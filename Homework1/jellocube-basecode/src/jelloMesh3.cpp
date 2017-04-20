#include "JelloMesh3.h"
#include <GL/glut.h>
#include <algorithm>



// TODO Play around with the numbers
	//Kd
		//Kd is the coefficient of drag-resists motion, "It is highly recommended that at least a small amount of drag be applied to each particle... Excessive drag, however makes it apear that the particles are floatin in molasses"- Witkin, A. (1997). Physically Based Modeling: Principals and Practice Particle System Dynamics
		//Kd is dampening term
		//Kd has to do with velocities
	//Ks
		//Ks is spring/elastic term 
	//Different Types of Spring Systems:
		//Partices, Structural Spring = line between particles, bend springs is between every two particles, shear are diagonally between particles, What is penalty and attachment?
double JelloMesh3::g_structuralKs = 4500.0;
double JelloMesh3::g_structuralKd = 4.0;
double JelloMesh3::g_shearKs = 4500.0;
double JelloMesh3::g_shearKd = 3.0;
double JelloMesh3::g_bendKs = 5000.0;
double JelloMesh3::g_bendKd = 5.0;
double JelloMesh3::g_penaltyKs = 4500.0;
double JelloMesh3::g_penaltyKd = 5.0;

JelloMesh3::JelloMesh3() :
	m_integrationType(JelloMesh3::RK4), m_drawflags(MESH | STRUCTURAL),
	m_cols(0), m_rows(0), m_stacks(0), m_width(0.0), m_height(0.0), m_depth(0.0)
{
	SetSize(1.0, 1.0, 1.0);
	SetGridSize(6, 6, 6);
}

JelloMesh3::~JelloMesh3()
{
}

void JelloMesh3::Reset()
{
	InitJelloMesh3();
}

JelloMesh3::Particle& JelloMesh3::GetParticle(JelloMesh3::ParticleGrid& grid, int i, int j, int k)
{
	return grid[i][j][k];
}

JelloMesh3::Particle& JelloMesh3::GetParticle(JelloMesh3::ParticleGrid& grid, int idx)
{
	int i, j, k;
	GetCell(idx, i, j, k);
	return GetParticle(grid, i, j, k);
}

const JelloMesh3::Particle& JelloMesh3::GetParticle(const JelloMesh3::ParticleGrid& grid, int i, int j, int k) const
{
	return grid[i][j][k];
}

const JelloMesh3::Particle& JelloMesh3::GetParticle(const JelloMesh3::ParticleGrid& grid, int idx) const
{
	int i, j, k;
	GetCell(idx, i, j, k);
	return GetParticle(grid, i, j, k);
}

bool JelloMesh3::isInterior(const JelloMesh3::Spring& s) const
{
	int i1, j1, k1, i2, j2, k2;
	GetCell(s.m_p1, i1, j1, k1); //particle 1
	GetCell(s.m_p2, i2, j2, k2); //particle 2
	return isInterior(i1, j1, k1) || isInterior(i2, j2, k2);
}

bool JelloMesh3::isInterior(int idx) const
{

	int i, j, k;
	GetCell(idx, i, j, k);

	return isInterior(i, j, k);
}

bool JelloMesh3::isInterior(int i, int j, int k) const
{
	return (i*j*k*(m_rows - i)*(m_cols - j)*(m_stacks - k) != 0);
}

void JelloMesh3::SetGridSize(int cols, int rows, int stacks)
{
	m_cols = cols;
	m_rows = rows;
	m_stacks = stacks;

	if (m_cols > 0 && m_rows > 0 && m_stacks > 0)
	{
		m_vparticles.resize(m_rows + 1);
		for (int i = 0; i < m_rows + 1; i++)
		{
			m_vparticles[i].resize(m_cols + 1);
			for (int j = 0; j < m_cols + 1; j++)
			{
				m_vparticles[i][j].resize(m_stacks + 1);
			}
		}
	}
	InitJelloMesh3();
}

int JelloMesh3::GetGridCols() const
{
	return m_cols;
}

int JelloMesh3::GetGridRows() const
{
	return m_rows;
}

int JelloMesh3::GetGridStacks() const
{
	return m_stacks;
}

void JelloMesh3::SetSize(float width, float height, float depth)
{
	m_width = width;
	m_height = height;
	m_depth = depth;
	InitJelloMesh3();
}

float JelloMesh3::GetWidth() const
{
	return m_width;
}
float JelloMesh3::GetHeight() const
{
	return m_height;
}

float JelloMesh3::GetDepth() const
{
	return m_depth;
}

int JelloMesh3::GetIndex(int i, int j, int k) const
{
	int cols = j;
	int rows = i*(m_rows + 1);
	int stacks = k*(m_cols + 1)*(m_stacks + 1);
	return cols + rows + stacks;
}

#define ROUND(x) (floor(x + 0.5))
#define FLOOR(x) (floor(x))
#define FRACT(x) (x - FLOOR(x))
void JelloMesh3::GetCell(int idx, int& i, int &j, int& k) const
{
	float rows = m_rows + 1;
	float cols = m_cols + 1;
	float stacks = m_stacks + 1;

	// derived from idx = cols*(rows*k + i) + j
	float tmp = FLOOR(idx / cols);
	j = (int)ROUND(cols*(FRACT(idx / cols)));
	i = (int)ROUND(rows*(FRACT(tmp / rows)));
	k = (int)FLOOR(tmp / rows);
}

void JelloMesh3::InitJelloMesh3()
{
	m_vsprings.clear();
	if (m_width < 0.01 || m_height < 0.01 || m_depth < 0.01) return;
	if (m_cols < 1 || m_rows < 1 || m_stacks < 1) return;

	// Init particles
	float wcellsize = m_width / m_cols;
	float hcellsize = m_height / m_rows;
	float dcellsize = m_depth / m_stacks;

	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				float x = -m_width*0.5f + wcellsize*i;
				float y = 0.5 + hcellsize*j;
				float z = -m_depth*0.5f + dcellsize*k;
				m_vparticles[i][j][k] = Particle(GetIndex(i, j, k), vec3(x-1.2, y+1, z));
			}
		}
	}

	// Setup structural, shear, and bend springs
	ParticleGrid& g = m_vparticles;
	for (int i = 0.0; i < m_rows + 1; i++)
	{
		for (int j = 0.0; j < m_cols + 1; j++)
		{
			for (int k = 0.0; k < m_stacks + 1; k++)
			{
				//Structural Springs
				if (j < m_cols) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 1, k));
				if (i < m_rows) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j, k));
				if (k < m_stacks) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 1));

				//if (j < m_cols-1) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 2, k));
				//if (i < m_rows-1) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i + 2, j, k));
				//if (k < m_stacks-1) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 2));

				//Bend Springs
				if (j < m_cols - 1) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 2, k));
				if (i < m_rows - 1) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i + 2, j, k));
				if (k < m_stacks - 1) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 2));

				if (j < m_cols - 2) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 3, k));
				if (i < m_rows - 2) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i + 3, j, k));
				if (k < m_stacks - 2) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 3));

				if (j < m_cols - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 4, k));
				if (i < m_rows - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i + 4, j, k));
				if (k < m_stacks - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 4));

				if (j < m_cols - 4) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 5, k));
				if (i < m_rows - 4) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i + 5, j, k));
				if (k < m_stacks - 4) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 5));

				//if (j < m_cols - 5) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 6, k));
				//if (i < m_rows - 5) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i + 6, j, k));
				//if (k < m_stacks - 5) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 6));

				//Shear Springs
				if (i < m_rows && j < m_cols) {
					AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k));
					//AddShearSpring(GetParticle(g, i + 1, j, k), GetParticle(g, i, j + 1, k));
				}
				if (i < m_rows && k < m_stacks) {
					AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j, k + 1));
					//AddShearSpring(GetParticle(g, i + 1, j, k), GetParticle(g, i, j, k + 1));
				}
				if (j < m_cols && k < m_stacks) {
					AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 1, k + 1));
					//AddShearSpring(GetParticle(g, i, j, k + 1), GetParticle(g, i, j + 1, k));
				}

				//just playing around
				//if (i < m_rows && j < m_cols && k < m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k + 1));
				//}
				//if (i > m_rows && j > m_cols && k > m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k + 1));
				//}
				//if (i > m_rows && j > m_cols && k > m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k + 1));
				//}

				//if (i > 0.0 && j > m_cols && k < m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j + 1, k + 1));
				//}
				//if (i > 0.0 && j < m_cols && k < m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j + 1, k + 1));
				//}
				//if (i > 0.0 && j < m_cols && k > m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j + 1, k + 1));
				//}
				//if (i > 0.0 && j > m_cols && k > m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j + 1, k + 1));
				//}


				//if (i < m_rows && j > 0.0 && k < m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j - 1, k + 1));
				//}
				//if (i > m_rows && j > 0.0 && k < m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j - 1, k + 1));
				//}
				//if (i < m_rows && j > 0.0 && k > m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j - 1, k + 1));
				//}
				//if (i > m_rows && j > 0.0 && k > m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j - 1, k + 1));
				//}


				//if (i < m_rows && j > m_cols && k > 0.0) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k - 1));
				//}
				//if (i > m_rows && j > m_cols && k > 0.0) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k - 1));
				//}
				//if (i < m_rows && j < m_cols && k > 0.0) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k - 1));
				//}
				//if (i > m_rows && j < m_cols && k > 0.0) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k - 1));
				//}


				//if (i > 0.0 && j > 0.0 && k < m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j - 1, k + 1));
				//}
				//if (i > 0.0 && j > 0.0 && k > m_stacks) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j - 1, k + 1));
				//}

				//if (i > m_rows && j > 0.0 && k > 0.0) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j - 1, k - 1));
				//}
				//if (i < m_rows && j > 0.0 && k > 0.0) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j - 1, k - 1));
				//}

				//if (i > 0.0 && j < m_cols && k > 0.0) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j + 1, k - 1));
				//}
				//if (i > 0.0 && j > m_cols && k > 0.0) {
				//	AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j + 1, k - 1));
				//}
			}
		}
	}
	// Init mesh geometry
	m_mesh.clear();
	m_mesh.push_back(FaceMesh(*this, XLEFT));
	m_mesh.push_back(FaceMesh(*this, XRIGHT));
	m_mesh.push_back(FaceMesh(*this, YTOP));
	m_mesh.push_back(FaceMesh(*this, YBOTTOM));
	m_mesh.push_back(FaceMesh(*this, ZFRONT));
	m_mesh.push_back(FaceMesh(*this, ZBACK));
}

void JelloMesh3::AddStructuralSpring(Particle& p1, Particle& p2)
{
	double restLen = (p1.position - p2.position).Length();
	m_vsprings.push_back(Spring(STRUCTURAL, p1.index, p2.index, g_structuralKs, g_structuralKd, restLen));
}

void JelloMesh3::AddBendSpring(JelloMesh3::Particle& p1, JelloMesh3::Particle& p2)
{
	double restLen = (p1.position - p2.position).Length();
	m_vsprings.push_back(Spring(BEND, p1.index, p2.index, g_bendKs, g_bendKd, restLen));
}

void JelloMesh3::AddShearSpring(JelloMesh3::Particle& p1, JelloMesh3::Particle& p2)
{
	double restLen = (p1.position - p2.position).Length();
	m_vsprings.push_back(Spring(SHEAR, p1.index, p2.index, g_shearKs, g_shearKd, restLen));
}

void JelloMesh3::SetIntegrationType(JelloMesh3::IntegrationType type)
{
	m_integrationType = type;
}

JelloMesh3::IntegrationType JelloMesh3::GetIntegrationType() const
{
	return m_integrationType;
}

void JelloMesh3::SetDrawFlags(unsigned int flags)
{
	m_drawflags = flags;
}

unsigned int JelloMesh3::GetDrawFlags() const
{
	return m_drawflags;
}

void JelloMesh3::DrawMesh(const vec3& eyePos)
{
	const ParticleGrid& g = m_vparticles;
	float red[4] = { 1.0,0.4,0.4,0.8 };
	float white[4] = { 1.0,1.0,1.0,1.0 };
	float purple[4] = { 0.9,0.2,1.0,1.0 };
	float pink[4] = { 0.5,0.0,0.0,1.0 };
	float black[4] = { 0.0,0.0,0.0,1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	for (unsigned int i = 0; i < m_mesh.size(); i++)
	{
		m_mesh[i].CalcDistToEye(*this, eyePos);
	}
	std::sort(m_mesh.begin(), m_mesh.end(), FaceMesh::compare);
	for (unsigned int i = 0.0; i < m_mesh.size(); i++)
	{
		m_mesh[i].Draw(*this);
	}

	//glDisable(GL_LIGHTING);
	//for (unsigned int i = 0; i < m_mesh.size(); i++)
	//{        
	//   m_mesh[i].DrawNormals(*this);
	//}
}

void JelloMesh3::DrawSprings(double a)
{
	const ParticleGrid& g = m_vparticles;
	glBegin(GL_LINES);
	for (unsigned int i = 0; i < m_vsprings.size(); i++)
	{
		if (!(m_vsprings[i].m_type & m_drawflags)) continue;
		if (isInterior(m_vsprings[i])) continue;
		switch (m_vsprings[i].m_type)
		{
		case BEND:       glColor4f(1.0, 1.0, 0.0, a); break;
		case STRUCTURAL: glColor4f(1.0, 1.0, 0.0, a); break;
		case SHEAR:      glColor4f(0.0, 1.0, 1.0, a); break;
		};
		vec3 p1 = GetParticle(g, m_vsprings[i].m_p1).position;
		vec3 p2 = GetParticle(g, m_vsprings[i].m_p2).position;
		glVertex3f(p1[0], p1[1], p1[2]);
		glVertex3f(p2[0], p2[1], p2[2]);
	}
	glEnd();
}

void JelloMesh3::DrawCollisionNormals()
{
	const ParticleGrid& g = m_vparticles;
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	for (unsigned int i = 0; i < m_vcollisions.size(); i++)
	{
		Intersection intersection = m_vcollisions[i];
		if (isInterior(intersection.m_p)) continue;

		const Particle& pt = GetParticle(g, intersection.m_p);
		vec3 normal = intersection.m_normal;
		vec3 end = pt.position + 0.2 * normal;
		glVertex3f(pt.position[0], pt.position[1], pt.position[2]);
		glVertex3f(end[0], end[1], end[2]);
	}
	glEnd();
}

void JelloMesh3::DrawForces()
{
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle p = m_vparticles[i][j][k];
				if (isInterior(i, j, k)) continue;

				vec3 normal = p.force.Normalize();
				vec3 end = p.position + 0.1 * normal;
				glVertex3f(p.position[0], p.position[1], p.position[2]);
				glVertex3f(end[0], end[1], end[2]);
			}
		}
	}
	glEnd();
}

void JelloMesh3::Draw(const vec3& eyePos)
{
	if (m_drawflags & MESH) DrawMesh(eyePos);

	if (m_drawflags & (STRUCTURAL | BEND | SHEAR))
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glLineWidth(1.0);
		DrawSprings(0.2);
		glLineWidth(1.5);
		glEnable(GL_DEPTH_TEST);
		DrawSprings(0.4);
	}

	if (m_drawflags & NORMALS) DrawCollisionNormals();
	if (m_drawflags & FORCES) DrawForces();

	glEnable(GL_LIGHTING);
}

void JelloMesh3::Update(double dt, const World& world, const vec3& externalForces)
{
	m_externalForces = externalForces;
	
	CheckForCollisions(m_vparticles, world);
	ComputeForces(m_vparticles);
	ResolveContacts(m_vparticles);
	ResolveCollisions(m_vparticles);

	switch (m_integrationType)
	{
	case EULER: EulerIntegrate(dt); break;
	case MIDPOINT: MidPointIntegrate(dt); break;
	case RK4: RK4Integrate(dt); break;
	}
}

void JelloMesh3::CheckForCollisions(ParticleGrid& grid, const World& world)
{
	m_vcontacts.clear();
	m_vcollisions.clear();

	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& p = GetParticle(grid, i, j, k);

				// 1. Check collisions with world objects 
				for (unsigned int i = 0; i < world.m_shapes.size(); i++)
				{
					Intersection intersection;
					if (world.m_shapes[i]->GetType() == World::CYLINDER &&
						CylinderIntersection(p, (World::Cylinder*) world.m_shapes[i], intersection))
					{
						if(intersection.m_type == CONTACT)
							m_vcontacts.push_back(intersection);

						else if (intersection.m_type == COLLISION)
							m_vcontacts.push_back(intersection);

					}
					else if (world.m_shapes[i]->GetType() == World::GROUND &&
						FloorIntersection(p, intersection))
					{
						if (intersection.m_type == CONTACT)
							m_vcontacts.push_back(intersection);

						else if (intersection.m_type == COLLISION)
							m_vcontacts.push_back(intersection);
					}
				}
			}
		}
	}
}

void JelloMesh3::ComputeForces(ParticleGrid& grid)
{
	// Add external forces to all points
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& p = GetParticle(grid, i, j, k);
				p.force = m_externalForces * p.mass;
			}
		}
	}

	// Update springs
	for (unsigned int i = 0; i < m_vsprings.size(); i++)
	{
		Spring& spring = m_vsprings[i];
		Particle& a = GetParticle(grid, spring.m_p1);
		Particle& b = GetParticle(grid, spring.m_p2);

		//define spring variables
		double Ks = spring.m_Ks; //Ks is spring/elastic term 
		double Kd = spring.m_Kd; //Kd is the coefficient of drag-resists motion, "It is highly recommended that at least a small amount of drag be applied to each particle... Excessive drag, however makes it apear that the particles are floatin in molasses"- Witkin, A. (1997). Physically Based Modeling: Principals and Practice Particle System Dynamics
								 //Kd is dampening term
								 //Kd has to do with velocities			
		double R = spring.m_restLen; //R =rest length
		vec3 diff = a.position - b.position; //difference in vector position
		vec3 diffv = b.velocity - a.velocity; //difference in vector velocity
		double dist = diff.Length();

		//equation from Spring Forces (Advanced)
		if (dist != 0)
		{
			vec3 force = -(Ks*(dist - R) + Kd* (diffv*diff / dist))*(diff / dist);//-[ks(|L|-R)+kd((i*L)/|L|)](L/|L|)
		   //Newtons 3rd law: equal and opposite forces
			a.force += force;
			b.force += -force;
		}
	}
}

void JelloMesh3::ResolveContacts(ParticleGrid& grid)
{
	for (unsigned int i = 0; i < m_vcontacts.size(); i++)
	{
		
			const Intersection& contact = m_vcontacts[i];
		Particle& pt = GetParticle(grid, contact.m_p);
		vec3 normal = contact.m_normal;
		double dist = contact.m_distance;
		vec3 diff = -dist * normal;
		double Ks = g_penaltyKs;
		double Kd = g_penaltyKd;

		if (dist != 0) { //cannot equal zero
		pt.force = ((Ks*dist) + (Kd * Dot(pt.velocity, normal*dist)) / dist)*((normal*dist) / abs(dist));
		pt.velocity = (vec3(0.0, 1.0, 0.0)*Kd);
		pt.position = pt.position - (dist*normal);//based on email from J.Kider
		}
	}
}

void JelloMesh3::ResolveCollisions(ParticleGrid& grid)
{
	for (unsigned int i = 0; i < m_vcollisions.size(); i++)
	{
		Intersection result = m_vcollisions[i];
		Particle& pt = GetParticle(grid, result.m_p);
		vec3 normal = result.m_normal;
		float dist = result.m_distance;
		float r = 0.8; //restitution coefficient
		pt.velocity = pt.velocity - (2 * (pt.velocity*normal))*(normal*r); //v'=v-2(v*N)Nr -from Collision Response (Bouncing) in webcourses
		pt.position = pt.position - (dist*normal);
	}
}

bool JelloMesh3::FloorIntersection(Particle& p, Intersection& intersection)
{
	//p.position[0]=x, p.position[1]=y; p.position[2]=z
	float COLLISION_DELTA = 0.5;
	if (p.position[1] <= 0.0)
	{
		intersection.m_p = p.index;
		intersection.m_distance = -p.position[1];// 0 is initial state and then computer initial minus final state
		intersection.m_normal = vec3(0.0, 1.0, 0.0); //normal vector-perpendicular to resting plane
		intersection.m_type = JelloMesh3::CONTACT;
		return true;
	}

	else if (p.position[1] >= 0.0 && p.position[1] <= 0.0 + COLLISION_DELTA)
	{
		intersection.m_p = p.index;
		intersection.m_distance = COLLISION_DELTA - p.position[1];// 0 is initial state and then computer initial minus final state
		intersection.m_normal = vec3(0.0, 1.0, 0.0); //normal vector-perpendicular to resting plane
		intersection.m_type = JelloMesh3::COLLISION;
		return true;
	}
	else { return false; }
}

bool JelloMesh3::CylinderIntersection(Particle& p, World::Cylinder* cylinder,
	JelloMesh3::Intersection& result)
{
	vec3 cylinderStart = cylinder->start;
	vec3 cylinderEnd = cylinder->end;
	vec3 cylinderAxis = cylinderEnd - cylinderStart;
	double cylinderRadius = cylinder->r;
	vec3 point = cylinderStart + ((Dot((p.position - cylinderStart), cylinderAxis) / cylinderAxis.SqrLength())*cylinderAxis);
	vec3 normal = p.position - point;

	double dist = normal.Length();
	normal = normal.Normalize();

	if (dist < cylinderRadius + 0.08)
	{
		result.m_p = p.index;
		result.m_distance = cylinderRadius;
		result.m_type = CONTACT;
		result.m_normal = normal;
		return true;
	}
	else if (dist < cylinderRadius && dist > cylinderRadius + 0.1)
	{
		result.m_p = p.index;
		result.m_distance = cylinderRadius;
		result.m_type = COLLISION;
		result.m_normal = normal;
		return true;
	}
	else { return false; };
}

void JelloMesh3::EulerIntegrate(double dt) // Y1=Y0+h f(X0,Y0); Yn+1 = Y+hf(Xn,Yn)
{ 
	//Poition=Original; Velocity =1st Derivative; Acceleration=2nd Derivative
	ParticleGrid& source = m_vparticles; // Source is a pointer to m_vparticles which first shows up on line 87. m_vparticle is a vector. ParticleGrid is a 3D Vector
	for (int i = 0; i < m_rows + 1; i++) //(i)= x coordinate
	{
		for (int j = 0; j < m_cols + 1; j++) //(j)= y coordinate. int=type of variable- integer. j++ means j=j+1 (incremental step of one). https://www.quora.com/What-does-%2B-mean-in-C-programming
		{
			for (int k = 0; k < m_stacks + 1; k++) //(k)= z coordinate
			{
				Particle& p = GetParticle(source, i, j, k);//(i, j, k) is (x, y, z); p.particle's original position
				p.position = p.position + dt*p.velocity; //Yn+1 = Y+hf(Xn,Yn); OR X0(t0+h)=X0+hXdot(t0); Where p.position (X1) is equal to the original position (X0) plus the step size (h) multiplied by the time derivative of (X0)
				p.velocity = p.velocity + (dt*p.force)*(1.0 / p.mass);//p.velocity is the derivative of p.position (X0); Look at Linear Motion In Webcourses- velocity= derivative of F/mass plus the original velocity (V0); derivative of F/mass =derivative of acceleration
			}
		}
	}
}



void JelloMesh3::MidPointIntegrate(double dt)
{
	double halfdt = 0.5 * dt; //dt is h. h is the step size. halfdt= half a time step, or midpoint
	ParticleGrid target = m_vparticles;  // target is a copy! A copy of what?
	ParticleGrid& source = m_vparticles;  // Source is a pointer to m_vparticles which first shows up on line 87. m_vparticle is a vector. ParticleGrid is a 3D Vector
										  // Step 1. Compute K1
	ParticleGrid accum1 = m_vparticles; //what does accum1 mean?
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& s = GetParticle(source, i, j, k); //initial position
				Particle& k1 = GetParticle(accum1, i, j, k);
				k1.velocity = halfdt * s.velocity;
				k1.force = halfdt * s.force * 1 / s.mass;

				Particle& t = GetParticle(target, i, j, k);
				t.position = s.position + k1.velocity;
				t.velocity = s.velocity + k1.force;

			}
		}
	}

	ComputeForces(target);

	// Step 2 compute K2
	ParticleGrid accum2 = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& t = GetParticle(target, i, j, k);
				Particle& k2 = GetParticle(accum2, i, j, k);

				k2.force = halfdt * t.force * 1 / t.mass;
				k2.velocity = halfdt * t.velocity;

				Particle& s = GetParticle(source, i, j, k);
				t.velocity = s.velocity + k2.force;
				t.position = s.position + k2.velocity;
			}
		}
	}
}

void JelloMesh3::RK4Integrate(double dt)
{
	double halfdt = 0.5 * dt; //dt is equal to h. h is the step size
	ParticleGrid target = m_vparticles;  // target is a copy!
	ParticleGrid& source = m_vparticles;  // source is a ptr!
										  // Step 1. Compute K1
	ParticleGrid accum1 = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& s = GetParticle(source, i, j, k);

				Particle& k1 = GetParticle(accum1, i, j, k);
				k1.force = halfdt * s.force * 1 / s.mass;
				k1.velocity = halfdt * s.velocity;

				Particle& t = GetParticle(target, i, j, k);
				t.velocity = s.velocity + k1.force;
				t.position = s.position + k1.velocity;
			}
		}
	}

	ComputeForces(target);

	// Step 2. Compute K2
	ParticleGrid accum2 = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& t = GetParticle(target, i, j, k);
				Particle& k2 = GetParticle(accum2, i, j, k);

				k2.force = halfdt * t.force * 1 / t.mass;
				k2.velocity = halfdt * t.velocity;

				Particle& s = GetParticle(source, i, j, k);
				t.velocity = s.velocity + k2.force;
				t.position = s.position + k2.velocity;
			}
		}
	}

	ComputeForces(target);

	// Step 3. Compute K3
	ParticleGrid accum3 = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& t = GetParticle(target, i, j, k);
				Particle& k3 = GetParticle(accum3, i, j, k);

				k3.force = dt * t.force * 1 / t.mass;
				k3.velocity = dt * t.velocity;

				Particle& s = GetParticle(source, i, j, k);
				t.velocity = s.velocity + k3.force;
				t.position = s.position + k3.velocity;
			}
		}
	}
	ComputeForces(target);

	// Step 4. Compute K4
	ParticleGrid accum4 = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& t = GetParticle(target, i, j, k);
				Particle& k4 = GetParticle(accum4, i, j, k);

				k4.force = dt * t.force * 1 / t.mass;
				k4.velocity = dt * t.velocity;
			}
		}
	}

	// Put it all together. Compute RK4
	double asixth = 1 / 6.0;
	double athird = 1 / 3.0;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& p = GetParticle(m_vparticles, i, j, k);
				Particle& k1 = GetParticle(accum1, i, j, k);
				Particle& k2 = GetParticle(accum2, i, j, k);
				Particle& k3 = GetParticle(accum3, i, j, k);
				Particle& k4 = GetParticle(accum4, i, j, k);

				p.velocity = p.velocity + asixth * k1.force +
					athird * k2.force + athird * k3.force + asixth * k4.force;

				p.position = p.position + asixth * k1.velocity +
					athird * k2.velocity + athird * k3.velocity + asixth * k4.velocity;
			}
		}
	}
}


//---------------------------------------------------------------------

// Spring

//---------------------------------------------------------------------

JelloMesh3::Spring::Spring() :
	m_type(JelloMesh3::STRUCTURAL),
	m_p1(-1),
	m_p2(-1),
	m_Ks(1.0), m_Kd(1.0), m_restLen(1.0)
{
}

JelloMesh3::Spring::Spring(const JelloMesh3::Spring& p) :
	m_type(p.m_type), m_p1(p.m_p1), m_p2(p.m_p2),
	m_Ks(p.m_Ks), m_Kd(p.m_Kd), m_restLen(p.m_restLen)
{
}

JelloMesh3::Spring& JelloMesh3::Spring::operator=(const JelloMesh3::Spring& p)
{
	if (&p == this) return *this;
	m_type = p.m_type;
	m_p1 = p.m_p1;
	m_p2 = p.m_p2;
	m_Ks = p.m_Ks;
	m_Kd = p.m_Kd;
	m_restLen = p.m_restLen;
	return *this;
}

JelloMesh3::Spring::Spring(JelloMesh3::SpringType t,
	int p1, int p2, double Ks, double Kd, double restLen) :
	m_type(t), m_Ks(Ks), m_Kd(Kd), m_p1(p1), m_p2(p2), m_restLen(restLen)
{
}

//---------------------------------------------------------------------

// Particle

//---------------------------------------------------------------------

JelloMesh3::Particle JelloMesh3::Particle::EMPTY;

JelloMesh3::Particle::Particle(int idx, const vec3& p, const vec3& v, double m)
{
	index = idx;
	position = p;
	velocity = v;
	force = vec3(0, 0, 0);
	mass = m;
}

JelloMesh3::Particle::Particle() : index(-1), position(0, 0, 0), velocity(0, 0, 0), force(0, 0, 0), mass(1.0)
{
}

JelloMesh3::Particle::Particle(const JelloMesh3::Particle& p) :
	index(p.index), position(p.position), velocity(p.velocity), force(p.force), mass(p.mass)
{
}

JelloMesh3::Particle& JelloMesh3::Particle::operator=(const JelloMesh3::Particle& p)
{
	if (&p == this) return *this;

	index = p.index;
	position = p.position;
	velocity = p.velocity;
	force = p.force;
	mass = p.mass;
	return *this;
}



//---------------------------------------------------------------------

// Intersection

//---------------------------------------------------------------------



JelloMesh3::Intersection::Intersection() :

	m_p(-1), m_normal(0, 0, 0), m_distance(0), m_type(CONTACT)

{

}



JelloMesh3::Intersection::Intersection(const JelloMesh3::Intersection& p) :

	m_p(p.m_p), m_normal(p.m_normal), m_distance(p.m_distance), m_type(p.m_type)

{

}



JelloMesh3::Intersection& JelloMesh3::Intersection::operator=(const JelloMesh3::Intersection& p)

{

	if (&p == this) return *this;

	m_p = p.m_p;

	m_normal = p.m_normal;

	m_distance = p.m_distance;

	m_type = p.m_type;

	return *this;

}



JelloMesh3::Intersection::Intersection(IntersectionType type, int p, const vec3& normal, double d) :

	m_p(p), m_normal(normal), m_distance(d), m_type(type)

{

}





//---------------------------------------------------------------------

// Drawing

//---------------------------------------------------------------------



void JelloMesh3::FaceMesh::Draw(const JelloMesh3& m)

{

	const ParticleGrid& g = m.m_vparticles;

	for (unsigned int strip = 0; strip < m_strips.size(); strip++)

	{

		const std::vector<int>& points = m_strips[strip];



		glBegin(GL_TRIANGLE_STRIP);

		for (unsigned int pi = 0; pi < points.size(); pi++)

		{

			int idx = points[pi];

			vec3 p = m.GetParticle(g, idx).position;



			vec3 n(0, 0, 0);

			const std::vector<int>& neighbors = m_neighbors[idx];

			if (neighbors.size() > 0)

			{

				vec3 pup = m.GetParticle(g, neighbors[0]).position;

				vec3 pdown = m.GetParticle(g, neighbors[1]).position;

				vec3 pleft = m.GetParticle(g, neighbors[2]).position;

				vec3 pright = m.GetParticle(g, neighbors[3]).position;



				vec3 n1 = -((pright - p) ^ (pup - p));

				vec3 n2 = -((pdown - p) ^ (pright - p));

				vec3 n3 = -((pleft - p) ^ (pdown - p));

				vec3 n4 = -((pup - p) ^ (pleft - p));



				n = n1 + n2 + n3 + n4;

				n = n.Normalize();

			}



			glNormal3f(n[0], n[1], n[2]);

			glVertex3f(p[0], p[1], p[2]);

		}

		glEnd();

	}

}



void JelloMesh3::FaceMesh::DrawNormals(const JelloMesh3& m)

{

	glDisable(GL_LIGHTING);



	glBegin(GL_LINES);

	glColor3f(0.0, 1.0, 0.0);



	const ParticleGrid& g = m.m_vparticles;

	for (unsigned int strip = 0; strip < m_strips.size(); strip++)

	{

		const std::vector<int>& points = m_strips[strip];

		for (unsigned int pi = 0; pi < points.size(); pi++)

		{

			int idx = points[pi];

			vec3 p = m.GetParticle(g, idx).position;



			const std::vector<int>& neighbors = m_neighbors[idx];

			if (neighbors.size() == 0) continue;



			vec3 pup = m.GetParticle(g, neighbors[0]).position;

			vec3 pdown = m.GetParticle(g, neighbors[1]).position;

			vec3 pleft = m.GetParticle(g, neighbors[2]).position;

			vec3 pright = m.GetParticle(g, neighbors[3]).position;



			vec3 n1 = -((pright - p) ^ (pup - p));

			vec3 n2 = -((pdown - p) ^ (pright - p));

			vec3 n3 = -((pleft - p) ^ (pdown - p));

			vec3 n4 = -((pup - p) ^ (pleft - p));



			vec3 n = n1 + n2 + n3 + n4;

			n = n.Normalize();



			vec3 end = p + 0.2 * n;

			glVertex3f(p[0], p[1], p[2]);

			glVertex3f(end[0], end[1], end[2]);

		}

	}



	glEnd();

	glEnable(GL_LIGHTING);

}



#define R(i) max(0, min(i, m.m_rows)) // CLAMP row index

#define C(j) max(0, min(j, m.m_cols)) // CLAMP col index

#define D(j) max(0, min(j, m.m_stacks)) // CLAMP stack index

JelloMesh3::FaceMesh::FaceMesh(const JelloMesh3& m, JelloMesh3::Face f)

{

	const ParticleGrid& g = m.m_vparticles;

	switch (f)

	{

	case ZFRONT:

		m_strips.resize(m.m_rows);

		for (int i = 0; i < m.m_rows + 1; i++)

			for (int j = 0; j < m.m_cols + 1; j++)

			{

				if (i < m.m_rows)

				{

					m_strips[i].push_back(m.GetIndex(i + 1, j, 0));

					m_strips[i].push_back(m.GetIndex(i, j, 0));

				}



				std::vector<int> neighbors;

				neighbors.push_back(m.GetIndex(R(i), C(j + 1), D(0)));

				neighbors.push_back(m.GetIndex(R(i), C(j - 1), D(0)));

				neighbors.push_back(m.GetIndex(R(i - 1), C(j), D(0)));

				neighbors.push_back(m.GetIndex(R(i + 1), C(j), D(0)));

				m_neighbors[m.GetIndex(i, j, 0)] = neighbors;

			}

		break;

	case ZBACK:

		m_strips.resize(m.m_rows);

		for (int i = 0; i < m.m_rows + 1; i++)

			for (int j = 0; j < m.m_cols + 1; j++)

			{

				if (i < m.m_rows)

				{

					m_strips[i].push_back(m.GetIndex(i + 1, j, m.m_stacks));

					m_strips[i].push_back(m.GetIndex(i, j, m.m_stacks));

				}



				std::vector<int> neighbors;

				neighbors.push_back(m.GetIndex(R(i + 1), C(j), D(m.m_stacks)));

				neighbors.push_back(m.GetIndex(R(i - 1), C(j), D(m.m_stacks)));

				neighbors.push_back(m.GetIndex(R(i), C(j - 1), D(m.m_stacks)));

				neighbors.push_back(m.GetIndex(R(i), C(j + 1), D(m.m_stacks)));

				m_neighbors[m.GetIndex(i, j, m.m_stacks)] = neighbors;

			}

		break;

	case XLEFT:

		m_strips.resize(m.m_cols);

		for (int j = 0; j < m.m_cols + 1; j++)

			for (int k = 0; k < m.m_stacks + 1; k++)

			{

				if (j < m.m_cols)

				{

					m_strips[j].push_back(m.GetIndex(0, j + 1, k));

					m_strips[j].push_back(m.GetIndex(0, j, k));

				}



				std::vector<int> neighbors;

				neighbors.push_back(m.GetIndex(R(0), C(j), D(k + 1)));

				neighbors.push_back(m.GetIndex(R(0), C(j), D(k - 1)));

				neighbors.push_back(m.GetIndex(R(0), C(j - 1), D(k)));

				neighbors.push_back(m.GetIndex(R(0), C(j + 1), D(k)));

				m_neighbors[m.GetIndex(0, j, k)] = neighbors;

			}

		break;

	case XRIGHT:

		m_strips.resize(m.m_cols);

		for (int j = 0; j < m.m_cols + 1; j++)

			for (int k = 0; k < m.m_stacks + 1; k++)

			{

				if (j < m.m_cols)

				{

					m_strips[j].push_back(m.GetIndex(m.m_rows, j + 1, k));

					m_strips[j].push_back(m.GetIndex(m.m_rows, j, k));

				}



				std::vector<int> neighbors;

				neighbors.push_back(m.GetIndex(R(m.m_rows), C(j + 1), D(k)));

				neighbors.push_back(m.GetIndex(R(m.m_rows), C(j - 1), D(k)));

				neighbors.push_back(m.GetIndex(R(m.m_rows), C(j), D(k - 1)));

				neighbors.push_back(m.GetIndex(R(m.m_rows), C(j), D(k + 1)));

				m_neighbors[m.GetIndex(m.m_rows, j, k)] = neighbors;

			}

		break;

	case YBOTTOM:

		m_strips.resize(m.m_rows);

		for (int i = 0; i < m.m_rows + 1; i++)

			for (int k = 0; k < m.m_stacks + 1; k++)

			{

				if (i < m.m_rows)

				{

					m_strips[i].push_back(m.GetIndex(i + 1, 0, k));

					m_strips[i].push_back(m.GetIndex(i, 0, k));

				}



				std::vector<int> neighbors;

				neighbors.push_back(m.GetIndex(R(i + 1), C(0), D(k)));

				neighbors.push_back(m.GetIndex(R(i - 1), C(0), D(k)));

				neighbors.push_back(m.GetIndex(R(i), C(0), D(k - 1)));

				neighbors.push_back(m.GetIndex(R(i), C(0), D(k + 1)));

				m_neighbors[m.GetIndex(i, 0, k)] = neighbors;

			}

		break;

	case YTOP:

		m_strips.resize(m.m_rows);

		for (int i = 0; i < m.m_rows + 1; i++)

			for (int k = 0; k< m.m_stacks + 1; k++)

			{

				if (i < m.m_rows)

				{

					m_strips[i].push_back(m.GetIndex(i + 1, m.m_cols, k));

					m_strips[i].push_back(m.GetIndex(i, m.m_cols, k));

				}



				std::vector<int> neighbors;

				neighbors.push_back(m.GetIndex(R(i), C(m.m_cols), D(k + 1)));

				neighbors.push_back(m.GetIndex(R(i), C(m.m_cols), D(k - 1)));

				neighbors.push_back(m.GetIndex(R(i - 1), C(m.m_cols), D(k)));

				neighbors.push_back(m.GetIndex(R(i + 1), C(m.m_cols), D(k)));

				m_neighbors[m.GetIndex(i, m.m_cols, k)] = neighbors;

			}

		break;

	}

}



void JelloMesh3::FaceMesh::CalcDistToEye(const JelloMesh3& m, const vec3& eyePos)

{

	std::vector<int> points = m_strips[(int)(m_strips.size()*0.5)];

	int idx = points[(int)(points.size()*0.5)];

	vec3 pos = m.GetParticle(m.m_vparticles, idx).position;

	distToEye = (pos - eyePos).Length();

}



bool JelloMesh3::FaceMesh::compare(const FaceMesh& one, const FaceMesh& other)

{

	return one.distToEye > other.distToEye;

}
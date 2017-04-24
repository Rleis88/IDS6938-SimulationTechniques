// Agent.cpp: implementation of the SIMAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Behavior.h"
#include "Agent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//Construct static variables
//Their real values are set in static function SIMAgent::InitValues()
vector<SIMAgent*> SIMAgent::agents;
bool SIMAgent::debug = false;
float SIMAgent::radius = 20.0;
float SIMAgent::Mass = 1.0;
float SIMAgent::Inertia = 1.0;
float SIMAgent::MaxVelocity = 20.0;
float SIMAgent::MaxForce = 10.0;
float SIMAgent::MaxTorque = 40.0;
float SIMAgent::MaxAngVel = 10.0;
float SIMAgent::Kv0 = 1.0;
float SIMAgent::Kp1 = 1.0;
float SIMAgent::Kv1 = 1.0;
float SIMAgent::KArrival = 1.0;
float SIMAgent::KDeparture = 1.0;
float SIMAgent::KNoise = 1.0;
float SIMAgent::KWander = 1.0;
float SIMAgent::KAvoid = 1.0;
float SIMAgent::TAvoid = 1.0;
float SIMAgent::RNeighborhood = 1.0;
float SIMAgent::KSeparate = 1.0;
float SIMAgent::KAlign = 1.0;
float SIMAgent::KCohesion = 1.0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////////////// 
vec2 SIMAgent::WorldToLocal(vec2 &w)
{
	vec2 l;
	float s = sin(state[1]);
	float c = cos(state[1]);
	l[0] = c * w[0] + s * w[1];
	l[1] = -s * w[0] + c * w[1];
	return l;
}

vec2 SIMAgent::LocalToWorld(vec2 &l)
{
	vec2 w;
	float s = sin(state[1]);
	float c = cos(state[1]);
	w[0] = c * l[0] - s * l[1];
	w[1] = s * l[0] + c * l[1];
	return w;
}

void SIMAgent::SetVTheta(vec2 &V)
{
	vd = V.Length();
	if (vd < 0.0001) {
		thetad = 0.0;
	}
	else {
		if (abs(V[0]) < 0.0001) {
			if (V[1] > 0)
				thetad = M_PI / 2.0;
			else
				thetad = M_PI / -2.0;
		}
		else
			thetad = atan2(V[1], V[0]);
	}

	ClampAngle(thetad);
}

SIMAgent::SIMAgent()
{
}

SIMAgent::~SIMAgent()
{
}

void SIMAgent::Display()
{
	glPushMatrix();
	glTranslatef(GPos[0], rootHeight[frameNum], GPos[1]);
	if (showLeader && this == SIMAgent::agents[0]) {
		float red[] = { 1.0, 0.0, 0.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
		glPushMatrix();
		glTranslatef(0.0, 100.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidCone(10.0, 20.0, 24, 24);
		glPopMatrix();
	}

	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	if (SIMAgent::debug) {
		glutSolidSphere(10.0, 24, 24);
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glRotatef(-state[1] / M_PI * 180.0, 0.0, 1.0, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0); glVertex3f(12 + state[2], 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glRotatef(-thetad / M_PI * 180.0, 0.0, 1.0, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0); glVertex3f(12 + vd, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glLineWidth(1.0);
		glEnable(GL_LIGHTING);
	}
	else {
		glRotatef(90.0f - state[1] * Rad2Deg, 0.0, 1.0, 0.0);
		//glutSolidSphere(6.0f, 12, 12);
		glCallList(AgentDisplay::listNames + frameNum);
	}
	glPopMatrix();
}

void SIMAgent::ClearAgents() {
	for (unsigned int i = 0; i < agents.size(); i++)
		delete SIMAgent::agents[i];
	SIMAgent::agents.clear();
}

SIMAgent::SIMAgent(float* color, CEnvironment* env) {
	memcpy(this->color, color, sizeof(float) * 3);
	dimState = 4;
	dimInput = 2;
	frameNum = rand() % totalFrames;
	this->env = env;
	float angle = float(rand() % 360) / 180.0 * M_PI;
	vWander[0] = cos(angle) * SIMAgent::KWander;
	vWander[1] = sin(angle) * SIMAgent::KWander;
	angle = float(rand() % 360) / 180.0 * M_PI;
	v0[0] = cos(angle) * SIMAgent::MaxVelocity / 2.0;
	v0[1] = sin(angle) * SIMAgent::MaxVelocity / 2.0;
	SIMAgent::agents.push_back(this);
}

void SIMAgent::SetInitState(float pos[], float angle)
{
	int i;
	GPos[0] = pos[0];
	GPos[1] = pos[1];
	for (i = 0; i < dimState; i++) {
		state[i] = 0.0;
	}
	for (i = 0; i < dimInput; i++)
		input[i] = 0.0;
	state[1] = angle;
}

void SIMAgent::Sense(int type)
{
	showLeader = (type == LEADER);
	goal = env->goal;
	switch (type) {
	case SEEK: Seek(); break;
	case FLEE: Flee(); break;
	case ARRIVAL: Arrival(); break;
	case DEPARTURE: Departure(); break;
	case WANDER: Wander(); break;
	case AVOID: Avoid(); break;
	case SEPARATION: Separation(); break;
	case ALIGNMENT: Alignment(); break;
	case COHESION: Cohesion(); break;
	case FLOCKING: Flocking(); break;
	case LEADER: Leader(); break;
	}
}

void SIMAgent::Act(float deltaT)
{
	int dframe;
	this->deltaT = deltaT;
	FindDeriv();
	UpdateState();
	if (abs(state[2]) < 0.001)
		dframe = 0;
	else {
		dframe = int(state[2] / SIMAgent::MaxVelocity * 2 + 1);
	}
	frameNum += dframe;
	if (frameNum >= totalFrames) {
		frameNum = frameNum - totalFrames;
	}
}

void SIMAgent::SetV0()
{
	v0 = env->goal - GPos;
	v0 = v0.Normalize() * SIMAgent::MaxVelocity / 2;
}

/*
Sets the intial Values
*/
void SIMAgent::InitValues()
{
	/*********************************************
	// TODO: Add code here
	Set initial value for control and behavior settings
	You need to find out appropriate values for:
	SIMAgent::Kv0, SIMAgent::Kp1, SIMAgent::Kv1, SIMAgent::KArrival, SIMAgent::KDeparture,
	SIMAgent::KNoise, SIMAgent::KWander, SIMAgent::KAvoid, SIMAgent::TAvoid, SIMAgent::RNeighborhood,
	SIMAgent::KSeparate, SIMAgent::KAlign, SIMAgent::KCohesion.
	*********************************************/

	//play around with these
	Kv0 = 10.0; //
	Kp1 = -90.0; //seems to make the agent walk straighter but walks past if set too low; negative values orient the agent in the correct direct for some reason and also less erratic movement.
	Kv1 = 40.0; // Heading -seems to make the radius of the circle either bigger or smaller
	KArrival = 0.1; //makes it slow the closer it gets to the target
	KDeparture = 0.5; //makes it slow the closer to the target and faster the farther away
	KNoise = 10.0; //random noise for wander
	KWander = 8.0; // damping term for wander; how strong or week the wandering force is-how much it changes per frame https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624
	KAvoid = 1.0; //
	TAvoid = 20.0; //
	RNeighborhood = 800.0; //
	KSeparate = 1000.0; //
	KAlign = 20.0; //
	KCohesion = 0.05; //
	
	//from https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp
	//Kv0 = 10.0;
	//Kp1 = 256;
	//Kv1 = 32;
	//KArrival = 0.05;
	//KDeparture = 10000;
	//KNoise = 10;
	//KWander = 8;
	//KAvoid = 1;
	//TAvoid = 20;
	//RNeighborhood = 800;
	//KSeparate = 1000;
	//KAlign = 20;
	//KCohesion = 0.05;
}

/*
*	You should apply the control rules given desired velocity vd and desired orientation thetad.
*/
	/*********************************************
	// TODO: Add code here
	*********************************************/
	/*
	* You should apply the control rules given desired velocity vd and desired orientation thetad.
	* Velocity control: input[0] = f = m * Kv0 * (vd - v)
	* Heading control: input[1] = tau = I * ( -Kv1 * thetaDot - Kp1 * theta + Kp1 * thetad)
	* This function sets input[0] and input[1] appropriately after being called.
	*/
	void SIMAgent::Control()
	{
		// From Piazza
		Truncate(vd, -SIMAgent::MaxVelocity, SIMAgent::MaxVelocity);
		input[0] = SIMAgent::Mass * SIMAgent::Kv0 * (vd - state[2]);
		Truncate(input[0], -SIMAgent::MaxForce, SIMAgent::MaxForce);

		double dangle = AngleDiff(state[1], thetad);
		input[1] = SIMAgent::Inertia * (Kp1 * dangle - Kv1 * state[3]);
		Truncate(input[1], -SIMAgent::MaxTorque, SIMAgent::MaxTorque);
	}

/*
*	Compute derivative vector given input and state vectors
*  This function sets derive vector to appropriate values after being called
*/
void SIMAgent::FindDeriv()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	//From Original Read Me File
	//* state[0] is the position of the agent in local body coordinates(almost useless in this project);
	//* state[1] is the orientation angle of the agent with respect to world(i.e.global) coordinates;
	//* state[2] is the velocity of the agent in local body coordinates.
	//* state[3] is the angular velocity of the agent in world/gobal coordinates.
	
	//* input[0] is the force in local body coordinates
	//* input[1] is the torque in local body coordinates
	//Why is there no force and torque for global??
	
	//* deriv[0] is the force in local body coordinates divided by the mass.
	//* deriv[1] is the torque in local body coordinates divided by the inertia.
	//* deriv[2] is the velocity of the agent in local body coordinates
	//* deriv[3] is the angular velocity of the agent in world coordinates
	
	//tried this code based on original read me file but it doesnt seem to work
	//deriv[0] = input[0] / Mass;
	//deriv[1] = input[1] / Inertia;
	//deriv[2] = state[2];
	//deriv[3] = state[3];

	deriv[0] = state[2];
	deriv[1] = state[3];
	deriv[2] = input[0] / Mass;
	deriv[3] = input[1] / Inertia;
	
	//Study Group- but I dont think this is right based on the Original Read me informaiton
	/*deriv[0] = 0;
	deriv[1] = state[3];
	deriv[2] = input[0] / Mass;
	deriv[3] = input[1] / Inertia - state[3];*/ //https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp//
	//deriv[3] = input[1] / (Inertia - state[3]); //Study Group--noticed this made the agent loop more

}

/*
*	Update the state vector given derivative vector
*  Compute global position and store it in GPos
*  Perform validation check to make sure all values are within MAX values
*/
void SIMAgent::UpdateState()
{
	for (int i = 0; i < dimState; i++) {
		state[i] += deriv[i] * deltaT; //Euler's method, where state[i] is the new position, deri[1] is the derivative of the new position and deltaT is the timestep; use i so that it could dynamically change
	}
	state[0] = 0.0; //initial state

	//Clamp(state[1], -M_PI, M_PI);
	ClampAngle(state[1]); //Study Group
	Truncate(state[2], -SIMAgent::MaxVelocity, SIMAgent::MaxVelocity);

	vec2 GVelocity;
	GVelocity[0] = state[2] * cos(state[1]);
	GVelocity[1] = state[2] * sin(state[1]);
	GPos += GVelocity;

	Truncate(GPos[0], -1.0 * env->groundSize, env->groundSize);
	Truncate(GPos[1], -1.0 * env->groundSize, env->groundSize);

	Truncate(state[3], -SIMAgent::MaxAngVel, SIMAgent::MaxAngVel);
}


/*
*  Seek behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Seek()
//the agent attempts to steer towards a specified target.
{
	/*********************************************
	// TODO: Add code here

	4/4/2017 Class Notes
	•	GPos-Global position
	•	tmp is Vd
	•	tmp=goal-GPos
	•	This is a vector tmp[0] tmp[1]
	•	v.y = tmp[0]
	•	v.x = tmp[1]
	•	Arctan in C++ = atan2
	•	return (cos theta d, sin theta d) part of the answer
	•	Vec 2 Vn = sim agent max velocity **in class he said Vn but in notes its vd
	•	Return vec 2
	•	Return vec2(cos theta d*Vn, sin theta d*Vn)
	•	Can add checks to make sure the agents aren’t flipped around (not required)
	https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616
	*********************************************/
	//why is this backwards?
	vec2 tmp;
	//double thetad;
	tmp = goal - GPos; //desired velocity; To seek the first thing we want to look is what is the Desired Velocity - the shortest path from the current position to the target.
	tmp.Normalize();
	thetad = atan2(tmp[1],tmp[0]); //desired orientation; The next parameter we need to derive is the new angle the agent should be targeting, again we are using our basic trigonometric properties 
	vd = MaxVelocity; //We also define how fast the agent moves in general, their MaxVelocity
	return vec2(cos(thetad)*vd, sin(thetad)*vd);//Then we need to return to the Cartesian coordinates
}

/*
*  Flee behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Flee()
//the agent attempts to steer away from a specified target.
{
	/*********************************************
	// TODO: Add code here
	
	4/4/2017 Class Notes
	•	Times vector by Pi= Thetad*m_Pi in code
		•	Said to multiply it in class but "add" it in the webcourses
	•	Go in the opposite direction
	https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616
	*********************************************/
	//why is this backwards?
	vec2 tmp;
	//double thetad;
	tmp = GPos-goal; //desired velocity; To seek the first thing we want to look is what is the Desired Velocity - the shortest path from the current position to the target.
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]); //desired orientation; The next parameter we need to derive is the new angle the agent should be targeting, again we are using our basic trigonometric properties 
	vd = MaxVelocity; //We also define how fast the agent moves in general, their MaxVelocity
	//thetad = thetad + M_PI; //opposite direction; You flee in the opposite direction,  the vector is pointing from the target to the agent.  So it is exactly the same as Seek except you just have add 180 degree to the Seek desired velocity angle 
	return vec2(cos(thetad)*vd, sin(thetad)*vd);//Then we need to return to the Cartesian coordinates

}

/*
*  Arrival behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  Arrival setting is in SIMAgent::KArrival
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Arrival()
//the agent attempts to steer towards a specified target and slows down when it gets close.
//Arrival and departure function much like seek and flee, except as the agent approaches the target, it slows down (for departure, the closer it is to the target, the faster it moves away).
{
	/*********************************************
	// TODO: Add code here

	4/4/2017 Notes Class Notes
	•	Same set up but now person is “arriving within a circle area around goal
	•	tmp=goal-Gpos
	•	dist= tmp.length();
		•	If (dist>0)
		•	Theta d=…(same as above)
		•	Account for radius
		•	Vn=Maxvelocity*dist/Radius of arrival
		•	Sim agent:: Maxvelocity;
		•	Return-check
			•	Return cos theta*Vn, Sin theta*Vn
			•	Or return original vector
	•	Your agent may circle around the goal
	*********************************************/
	
	//study group
	//subbing tmp for Vd like in class notes doesn't seem to work
	//vec2 tmp;
	//vec2 Vd = goal - GPos; //desired velocity; To seek the first thing we want to look is what is the Desired Velocity - the shortest path from the current position to the target.
	//double dist = Vd.Length();
	//thetad = atan2(Vd[1], Vd[0]); //The next parameter we need to derive is the new angle the agent should be targeting, again we are using our basic trigonometric properties 
	//vd = abs(Vd)*KArrival //Webcourses
	//vd = abs(dist)*KArrival; //webcourses
	//vd = Vd.Length()*KArrival; //Study group
	//thetad = thetad + M_PI; //arrival only, not in departure
	//double vn = MaxVelocity *(vd / radius);
	//if (dist > 0.0) { 

	//	return vec2(cos(thetad)*vd, sin(thetad)*vd);
	//}
	//else {
	//	return  vec2(cos(thetad)*vn, sin(thetad)*vn);
	//}
	//Then we need to return to the Cartesian coordinates
	
	//why is this backwards?
	vec2 tmp;
	tmp = goal - GPos;
	double dist = tmp.Length();
	vd = abs(dist)*KArrival;
	Truncate(vd, 0, MaxVelocity);// Truncate (Bevilacqua, 2012b) means to cut off; (value, min, max) "it will not exceed a certain maximum speed . A minimum speed can also be specified but defaults to zero."(Reynolds, 1987).
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);
}

/*
*  Departure behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  Departure setting is in KDeparture
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Departure()
//the agent attempts to steer away from a specified target and slows down after a point too.
//Arrival and departure function much like seek and flee, except as the agent approaches the target, it slows down (for departure, the closer it is to the target, the faster it moves away).
{
	/*********************************************
	// TODO: Add code here

	4/4/2017 Notes Class Notes
	•	Go in the opposite direction (similar to flee)
	*********************************************/
	//study group
	//vec2 tmp;
	//vec2 Vd = goal - GPos; //desired velocity; To seek the first thing we want to look is what is the Desired Velocity - the shortest path from the current position to the target.
	//double dist = Vd.Length();
	//thetad = atan2(Vd[1], Vd[0]); //The next parameter we need to derive is the new angle the agent should be targeting, again we are using our basic trigonometric properties 
	////vd = abs(Vd)*KDeparture //Webcourses
	//vd = abs(dist)*KDeparture; //webcourses
	////vd = Vd.Length()*KDeparture; //Study group
	//double vn = MaxVelocity *(vd / radius);//Study Group
	//if (dist > 0.0) { 

	//	return vec2(cos(thetad)*vd, sin(thetad)*vd);
	//}
	//else {
	//	return  vec2(cos(thetad)*vn, sin(thetad)*vn);
	//}
	//Then we need to return to the Cartesian coordinates
	//return vec2(cos(thetad)*vd, sin(thetad)*vd);

	//why is this backwards???
	vec2 tmp;
	tmp = GPos-goal;
	double dist = tmp.Length();
	vd = abs(dist)*KDeparture;
	Truncate(vd, 0, MaxVelocity);// Truncate (Bevilacqua, 2012b) means to cut off; (value, min, max) "it will not exceed a certain maximum speed . A minimum speed can also be specified but defaults to zero."(Reynolds, 1987). **what are we scaling (speed) against veocity here?
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	//thetad = thetad + M_PI;
	return vec2(cos(thetad)*vd, sin(thetad)*vd);
}

/*
*  Wander behavior
*  VWander is in vWander
*  V0(nominal velocity) is in v0
*  Wander setting is in KWander
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Wander()
//Wandering means the agent is moving around randomly.
{
	/*********************************************
	// TODO: Add code here

	//From Webcourses
	// Yet, another way to implement this is to pick a random angle multiply some random noise (Knoise) to the x and y directions of the velocity, and multiply a damping term (KWander).
	
	4/4/2017 Notes Class Notes
	•	Random goal number versus a fixed goal
	*********************************************/                   
	
	//study group
	//vec2 tmp;
	//double randomangle = double(rand() % 360) / 180.0 * M_PI; //pick random angle
	//vec2 tmp = vec2(cos(randomangle), sin(randomangle));
	//vec2 randomnoise = KNoise*tmp; //multiple by random noise
	//float combineL = sqrt((vWander[0] + randomnoise[0])*(vWander[0] + randomnoise[0]) + (vWander[1] + randomnoise[1])*(vWander[1] + randomnoise[1]));
	//vWander = KWander / combineL*(vWander + randomnoise); //multiply by KWander???????
	//vec2 Vdesired = v0 + vWander;
	//float vd = sqrt(Vdesired[0] * Vdesired[0] + Vdesired[1] * Vdesired[1]);
	//thetad = atan2(Vdesired[1], Vdesired[0]);
	//return vec2(cos(thetad)*vd, sin(thetad)*vd);
	//return tmp;

	//Needed in Wander behavior-from header file
	//Wander velocity
	//vec2 vWander;
	//Nominal velocity
	//vec2 v0;

	vec2 tmp;
	//vec2 CC;
	//vec2 displace;

	//Calculate Circle Center
	//tmp = goal - GPos;
	//CC = tmp; //create circle center clone
	//CC.Normalize(); //normalize
	//CC*tmp;//scale by circle distance

	//Calculate Displacement forces
	//displace = displace*radius;

	//Randomly change vector direction
	//from above
	//could also implement random number generator from HW2---will do this if I have time
	//float angle = float(rand() % 360) / 180.0 * M_PI;
	//v0[0] = cos(angle) * MaxVelocity / 2.0;
	//v0[1] = sin(angle) * MaxVelocity / 2.0;

	//Change wander angle for next frame
	//from above
	//could also implement random number generator from HW2---will do this if I have time
	//float angle = float(rand() % 360) / 180.0 * M_PI;
	//vWander[0] = cos(angle) * KWander;
	//vWander[1] = sin(angle) * KWander;
	
	//Calculate and return wander https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624
	//steering = wander()
	//steering = truncate(steering, max_force) //in control and update position
	//steering = steering / mass //in control and update position
	//velocity = truncate(velocity + steering, max_speed) //in control and update position
	//position = position + velocity //in control and update position
	//thetad = atan2(tmp[1], tmp[0]); //desired orientation; The next parameter we need to derive is the new angle the agent should be targeting, again we are using our basic trigonometric properties 
	//vd = MaxVelocity; //We also define how fast the agent moves in general, their MaxVelocity
	//return vec2(cos(thetad)*vd, sin(thetad)*vd);//Then we need to return to the Cartesian coordinates
	return tmp;




}

/*
*	Avoid behavior
*  Obstacles are in env->obstacles
*  Number of obstacles is env->obstaclesNum
*  env->obstacles[i][0] and env->obstacles[i][1] are the global position of the ith obstacle
*  env->obstacles[i][2] is the radius of the ith obstacle
*  Agent bounding sphere radius is in SIMAgent::radius
*  Avoidance settings are in SIMAgent::TAvoid and SIMAgent::KAvoid
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Avoid()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;
	
	return tmp;
}

/*
*	Separation behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Separation settings are in SIMAgent::RNeighborhood and SIMAgent::KSeperate
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Separation()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;

	return tmp;
}

/*
*	Alignment behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Alignment settings are in SIMAgent::RNeighborhood and SIMAgent::KAlign
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Alignment()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;

	return tmp;
}

/*
*	Cohesion behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Cohesion settings are in SIMAgent::RNeighborhood and SIMAgent::KCohesion
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Cohesion()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;


	return tmp;
}

/*
*	Flocking behavior
*  Utilize the Separation, Cohesion and Alignment behaviors to determine the desired velocity vector
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Flocking()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;

	return tmp;
}

/*
*	Flocking behavior
*  Utilize the Separation, Arrival behaviors to determine the desired velocity vector
*  You need to find the leader, who is always the first agent in SIMAgent::agents
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Leader()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;

	return tmp;
}
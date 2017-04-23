# Homework 3 : Agent based Simulation Assignment

## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

[University of Central Florida](http://www.ist.ucf.edu/grad/)

## Introduction
The goal of this assignment is to enable the behavioral animation of vehicle-like walking agents.

### An Agent is Defined as...

Sometimes, particularly in the context of steering behavior these agents may be refered to as autonomous characters or Non-Player Characters (NPC).

### Agent-Based Simulation is...

### Types of Agent-Based Simulation...


## Part 1: Steering Behaviors

### Background
To demonstrate my understanding of the problem. I have provided some background informaiton below.

#### Steering Behaviors Defined

*What are steering behaviors?*

In computer animaltion, *steering behaviors* can be defined as methematical formulas used to simulate "flocking" behvaiors similar to the movement of birds, schools of fish, and other groups of behavioral agents. Above, I introduced agents and agent-based simulation. Steering behaviors can help program the behavioral aspects of agents in a way that allows for close-to-natural, improvized movement in an efficient way using simple forces (called *steering forces*; [Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)). Types of steering behaviors and forces will be described in more detail later in the present document and implemented using C++ programing in Visual Studio.

#### Boids Model

*What methods can I use to simulate the steering behaviors of agents?*

The Boids Model was created in the late 80's by [Craig W. Reynolds](http://www.red3d.com/cwr/). Reynods created the model because at the time it was incredibly difficult to model the individual and complex paths of multiple computer animated entities. With then current techonology, it was difficult to maintain and edit paths (avoid collision) for larger groups of entities. Reynolds [(1987)](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db) stated "a better approach is needed for efficient, robust, and believable animation of flocks and related group motions," ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)). Thus, Reyonds in his 1987 paper -- *Flocks, Heards, and Schools: A Distributed Behvaioral Model* -- introduced the Boids Model, which stands for "bird-oid object" or "bird-like object," ([Kider, 2017a](https://webcourses.ucf.edu/courses/1246518/pages/boids?module_item_id=10564246)). Each object is an individual entity exhibiting simple behaviors-making Boids an agent-based model. You can view a video of the original Boids computer animaltion created by Reynods [here](https://www.youtube.com/watch?v=86iQiV3-3IA)

#### Implementation

*How does it work?*

The key to modeling this behavior is to utilize steering behaviors that are not based on global informaiton or path planning calculations, but rather on local information, ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)). This limited "local" informaiton derives from the forces (like velocity) created by neighboring agents, ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849); [Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)). This type of local informaiton allows the neighboring forces to produce complex movement but with a simple (and efficient) implementation method ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)) following the natural laws of physics ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)). Further, these forces remove the occurance of "abrubpt behavior" such as turning on a dime which is not how real groups of agents would behave naturally ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)).

*How do I use this method?*

The "birds" are modeled using something similar to a partical system, with the birds or entities serving as the "particles" and each exhibiting it's own behavior ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)). These particples crease "complex" shapes ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)) using velocity and position of multiple vectors to determine movement ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)). We also used a particle system during our Continuous Homework (HW) 1 Jello Cube Simulation. However, Boids is slightly different from a partical system in that 1) the particle is not represented by a "dot" but rather a shape, (in this case a human-like agent) allowing it to have an orientation; and, 2) the behavior is generally more complex for the Boid entities versus a particle ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)). Further, each agent can "percieve" the area (or "spherical neighborhood") around it ([Prinston, 2012](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf.)).

*Why use C++?*

Reynods suggests using object-oriented programing to model the agent's behaviors; he believes it is easy to store the behaviors as an object ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)). In this case I am using C++ as my choice of object-oriented programming language because it was required of the assignment.

#### Applications

* Flocks of birds ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db))
* Schools of fish ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db))
* Heards of animals ([Wikimedia Foundation Inc., 2017b](https://en.wikipedia.org/wiki/Boids))
* Swarm robotics ([Wikimedia Foundation Inc., 2017b](https://en.wikipedia.org/wiki/Boids))

### 1.a) Compute Derivative Vector and Initial Values

 The "boids" or agents similate a "flight-like" pattern by taking incremental "steps" or moves ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)), modeled uing Euler's Method (which we also learned and integrated into HW 1; [Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)).

![](images/Euler.JPG?raw=true)
[Source](https://webcourses.ucf.edu/courses/1246518/pages/eulers-method?module_item_id=10526148)

To calculate Eulers method, we need to determine the *derivative* and the *initial value*. We will also need a *time step* to calculate Euler; however, this is provided for us in the based code. I believe the time step is located in the Agent.h file under member variables as *deltaT*. This is confirmed in the code given by Dr. Kider for *SIMAgent::UpdateState()* which I will adress later in this document.


#### Find the Derivative

To implement *SIMAgent::FindDeriv()* I first looked up some example code. I found [this resource](https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp) to use as a starting point. A group of students and I also went through this during study group on 4/13/2017. However, based on the informaiton provided in the original Readme.md file, I believe the code we collaborated on in the study group was incorrect. To view more informaiton about the code we tried please see the Agent.cpp file under *SIMAgent::FindDeriv()*. Here you can see the information and additional notes commented out.

Below are the derivative vectors implemented in my code.

	deriv[0] = input[0] / Mass;
	deriv[1] = input[1] / Inertia;
	deriv[2] = state[2];
	deriv[3] = state[3];

#### Determine the Initial Values

To implement *SIMAgent::InitValues()* I first looked up some example code. I found [this resource](https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp) to use as a starting point.

Below are the initial values implemented in my code.

**remember to update this**

    Kv0 = 200.0;
	Kp1 = 15.0;
	Kv1 = 1.0;
	KArrival = 0.5;
	KDeparture = 10000.0;
	KNoise = 0.0;
	KWander = 8.0;
	KAvoid = 1.0;
	TAvoid = 20.0;
	RNeighborhood = 800.0;
	KSeparate = 1000.0;
	KAlign = 20.0;
	KCohesion = 0.05;

### Gifted Code
Dr. Kider provided the class with two different chunks of code, which included *SIMAgent::UpdateState()* and *SIMAgent::Control()*.

As stated above, these behaviors can be programed using Euler's Integration Method. Where, to move forward, the new poistion is found using the current position plus the velocity (time step multipled by the derivative of the previous position; [Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849); [Wikimedia Foundation, Inc., 2017a](https://en.wikipedia.org/wiki/Velocity)). However, I need to include more than just Euler's method to move the agent forward. As stated above, boids or agents have an orientation; thus, the velocity vector will have a direction. The direction of the agent determines where the agent is headed ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849). The length or magnatude of the velocity vector will determine how quickly (or how much) it moves within a frame ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)). The longer the length of the vector the faster the agent moves ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)); meaning, the farther away the agent is from the target, the faster it will "walk" to the target, getting slower the closer it gets. This will be particularly evident in the arrival and the departure behvaiors seen later. Further, to make sure that the velocity vector does not become greater (or faster) that what is naturally observed, it can be trucated to account for the max velocity, ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)). I don't want these fuctions to make the agent's movement to change abrupbtly. Thus, I need to make sure the steering forces mentioned above are in place ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)). I believe this is the purpose of these two functions.

Without Steering Forces| With Steering Forces
-------- | --------
![](images/steering_forces.png?raw=true)|![](images/steering_forces_seek_path.png?raw=true)

[Source](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)


#### Update State

The code given by Dr. Kider is shown below:

	for (int i = 0; i < dimState; i++) {
		state[i] += deriv[i] * deltaT;
	}
	state[0] = 0.0;

	ClampAngle(state[1]);
	Truncate(state[2], -SIMAgent::MaxVelocity, SIMAgent::MaxVelocity);

	vec2 GVelocity;
	GVelocity[0] = state[2] * cos(state[1]);
	GVelocity[1] = state[2] * sin(state[1]);
	GPos += GVelocity;

	Truncate(GPos[0], -1.0 * env->groundSize, env->groundSize);
	Truncate(GPos[1], -1.0 * env->groundSize, env->groundSize);

	Truncate(state[3], -SIMAgent::MaxAngVel, SIMAgent::MaxAngVel);

Euler's method can be seen in the second line in this chunk of code, where *state[i]* is the new position, *deriv[1]* is the derivative of the new position, and *deltaT* is the timestep. We use *i* so that it could dynamically update. *state[0]* sets the initial state for the agent. In the code provided, we were given *Clamp(state[1], -M_PI, M_PI)*; however, this code did not work when plugged in. During the 4/13/2017 study group, we went over how everyone adjusted this code to allow the program to run. Thus, I changed it to *ClampAngle(state[1])*.

#### Control

The code given by Dr. Kider is shown below:

    Truncate(vd, -SIMAgent::MaxVelocity, SIMAgent::MaxVelocity);
    input[0] = SIMAgent::Mass * SIMAgent::Kv0 * (vd - state[2]);
    Truncate(input[0], -SIMAgent::MaxForce, SIMAgent::MaxForce);

    double dangle = AngleDiff(state[1], thetad);
    input[1] = SIMAgent::Inertia * (Kp1 * dangle - Kv1 * state[3]);
    Truncate(input[1], -SIMAgent::MaxTorque, SIMAgent::MaxTorque);

### 1.b) Individual Behaviors

Reynold's suggested first to simulate the behavior of an individual agent ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)), as it is often easier to start with modeling a simple behavior and then adding complexity (group behvaiors). This also explains why we were instructed to complete this witin Part 1b. 

*Note: Each section title is linked to the corresponding WebCourses URL.*

#### [Seek](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616)

*Seeking* behavior is defined as "the agent attempts to steer towards a specified target, " ([Kider, 2017b](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616)).

Below is the code I implemented for *seek*.

	vec2 tmp;
	double thetad;
	tmp = goal - GPos;
	tmp.Normalize();
	thetad = atan2(tmp[1],tmp[0]);
	double vd = SIMAgent::MaxVelocity;
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

Where *tmp* is the desired velocity to the new "goal" position, *thetad* is the desired orientation, and *vd* is the max velocity. The desired velocity is "the shortest path from the current position to the target" ([Kider, 2017c](https://github.com/hepcatjk/IDS6938-SimulationTechniques)). The velocity vector for seek is calculated as: velocity = normalize(target - position) x max_velocity, ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)), which is why tmp is normalized in the code presented above. For *thetad* "we need to derive is the new angle the agent should be targeting, again we are using our basic trigonometric properties," ([Kider, 2017c](https://github.com/hepcatjk/IDS6938-SimulationTechniques)). The max velocity calculates how quickly the agent is moving ([Kider, 2017c](https://github.com/hepcatjk/IDS6938-SimulationTechniques)). Then the code should return the cartesian coordinates for the agent to go to ([Kider, 2017c](https://github.com/hepcatjk/IDS6938-SimulationTechniques)), which can be seen in the return statment.

*To view the notes associated with this code, please view my edited Agent.cpp file. I summarized the C++ notes for readability. We went through this peice of code during study group on 4/13/2017.*

#### [Flee](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616)

*Fleeing* behvaior is defined as "the agent attempts to steer away from a specified target," ([Kider, 2017b](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616)).

Below is the code I implemented for *flee*.

	vec2 tmp;
	double thetad;
	tmp = goal - GPos;
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	double vd = SIMAgent::MaxVelocity;
	thetad = thetad + M_PI;
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

The code for flee is similar to the code for seek. However, to account for the opposite direction/orientation, I've added pi to thetad to achieve the new desired velocity, which is denoted as  *thetad = thetad + M_PI*, ([Kider, 2017b](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616)).

*To view the notes associated with this code, please view my edited Agent.cpp file. I summarized the C++ notes for readability. We went through this peice of code during study group on 4/13/2017.*

#### [Arrival](https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664)

Below is the code I implemented for *arrival*. To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. We also went through this during study group on 4/13/2017.

	vec2 tmp;
	vec2 Vd = goal - GPos;
	double dist = Vd.Length();
	thetad = atan2(Vd[1], Vd[0]);
	vd = Vd.Length()*KArrival;
	thetad = thetad + M_PI;
	double vn = MaxVelocity *(vd/radius);
	if (dist > 0.0) {
		return vec2(cos(thetad)*vd, sin(thetad)*vd);
	}
	else {
		return  vec2(cos(thetad)*vn, sin(thetad)*vn);
	}

Another form of the code that I got to work is denoted below:

	vec2 tmp;
	vec2 Vd = goal - GPos;
	double dist = Vd.Length();
	thetad = atan2(Vd[1], Vd[0]);
	vd = abs(dist)*KArrival;
	thetad = thetad + M_PI;
	double vn = MaxVelocity *(vd / radius);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);


#### [Departure](https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664)

Below is the code I implemented for *arrival*. To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. We also went through this during study group on 4/13/2017.

	vec2 tmp;
	vec2 Vd = goal - GPos;
	double dist = Vd.Length();
	thetad = atan2(Vd[1], Vd[0]);
	vd = Vd.Length()*KDeparture;
	double vn = MaxVelocity *(vd / radius);
	if (dist > 0.0) {
		return vec2(cos(thetad)*vd, sin(thetad)*vd);
	}
	else {
		return  vec2(cos(thetad)*vn, sin(thetad)*vn);
	}

Another form of the code that I got to work is denoted below:

	vec2 tmp;
	vec2 Vd = goal - GPos;
	double dist = Vd.Length();
	thetad = atan2(Vd[1], Vd[0]);
	vd = abs(dist)*KDeparture;
	double vn = MaxVelocity *(vd / radius);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);


#### [Wander](https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154)


#### [Avoid](https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154)
There are two different methods approached to program obstical avoidance, the *force field approach* and the *steer-to-avoid approach* ([Prinston, 2012](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf)).

##### Force Field Approach
" Obstacles have a field of repulsion  Boids increasingly repulsed as they approach obstacle"
"Drawbacks:  Approaching a force in exactly the opposite direction  Flying alongside a wall"

##### Steer-To-Avoid Approach
" Boid only considers obstacles directly in front of it  Finds silhouette edge of obstacle closest to point of eventual impact  A vector is computed that will aim the boid at a point one body length beyond the silhouette edge"

#### Other individual behaviors include:
* **Pursuit**-
* **Containment**-
* **Wall Following**-
* **Path Following**-

([Prinston, 2012](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf))

Wall Following and Containment| Path Following
-------- | --------
![](images/wall.png?raw=true)|![](images/path.png?raw=true)

([Source](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf))

### 1.c) Group Behaviors:
Note: Each section title is linked to the corresponding WebCourses URL.
#### [Seperation](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)
"(a) separation,
which steers a boid away from its neighbors; Behavioral animation PDF article

#### [Cohesion](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)
(c) cohesion, which steers the boid toward the average position of its neighbors [Reyn87]."  Behavioral animation PDF article
#### [Alignment](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)
(b) alignment, which steers a boid such that its heading aligns with its neighbors;  Behavioral animation PDF article
#### [Flocking](https://webcourses.ucf.edu/courses/1246518/pages/flocking-and-leader-following?module_item_id=10573471)
#### [Leader Following](https://webcourses.ucf.edu/courses/1246518/pages/flocking-and-leader-following?module_item_id=10573471)

Limited information- based off of the velocity of the other agents -- Is this why there is a leader in the group behaviors

## Part 2 - Simulating a Simple Pedestrian Flow


### 2.a) Follow the Anylogic Example for the [Subway Entrance Example](https://help.anylogic.com/index.jsp?topic=/com.xj.anylogic.help/html/_PL/tutorial/Subway_Entrance.html)

<a href="http://www.youtube.com/watch?feature=player_embedded&v=8ESffmzlObc" target="_blank"><img src="http://img.youtube.com/vi/8ESffmzlObc/0.jpg" alt="Anylogic" width="850" height="490" border="1" /></a>
^^click me^^ *If that doesn't work click [here](https://www.youtube.com/watch?v=8ESffmzlObc)*

### 2.b) Create a Maze

### 2.c) Model and Analyze a Building/Floor/Outdoor Space/Stadium on Campus


## References

###Literature Sources
* Bevilacqua, F. (2012a). [Understanding Steering Behaviors: Seek](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849). Retrived from https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849

* Kider, J. (2017a). [Boids](https://webcourses.ucf.edu/courses/1246518/pages/boids?module_item_id=10564246) [Webcourse Module]. Retrived from https://webcourses.ucf.edu/courses/1246518/pages/boids?module_item_id=10564246

* Kider J. (2017b). [Seek and Flee](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616) [Webcourses Module]. Retrived from https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616

* Kider J. (2017c). [Agent.cpp](https://github.com/hepcatjk/IDS6938-SimulationTechniques). Retrived from https://github.com/hepcatjk/IDS6938-SimulationTechniques

* Reynods, C. W. (1987). [Flocks, heards, and schools: A distributed behvaioral model](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db). *Computer Graphics, 21*(4), p. 25-34.

* Prinston (2012). [Boids COS 426](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf). Retrived from http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf
* [Maze](https://www.bing.com/images/search?view=detailV2&ccid=RC36Xmth&id=75F0B2DFE037AAED3F66AA8ABF44C38C5FE859F4&q=maze&simid=608014100339818874&selectedIndex=25&ajaxhist=0)

* [Base Code Exmample](https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp)

* Wikimedia Foundation, Inc., (2017a).[Velocity](https://en.wikipedia.org/wiki/Velocity). Retrived from https://en.wikipedia.org/wiki/Velocity

* Wikimedia Foundation, Inc., (2017b). [Boids](https://en.wikipedia.org/wiki/Boids). Retrived from https://en.wikipedia.org/wiki/Boids

### Study Group
* 4/13/2017
*Note: I'm not 100% sure who all was in this group since I attended via skype (audio only). These we just the voices I could hear.*
	* Keith MacArthur
	* Sarah Matthews
	* Roberto Cabrera

## To Read
* http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db
* https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303
* http://www.red3d.com/cwr/steer/gdc99/
* http://www.red3d.com/cwr/steer/
* http://www.red3d.com/cwr/boids/
* http://www.red3d.com/cwr/nobump/nobump.html
* Behavioral Animation for Maya Particles Using Steering Forces
* https://runthemodel.com/models/204/


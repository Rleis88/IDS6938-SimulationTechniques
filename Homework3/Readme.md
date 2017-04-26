# Homework 3 : Agent-Based Simulation Assignment
**IDS6938-Simulation Techniques** - [University of Central Florida](http://www.ist.ucf.edu/grad/)

## Introduction
The goal of this assignment is to enable the behavioral animation of vehicle-like walking agents.

### Agents

To view the difinition and informaiton on agents [click here](https://webcourses.ucf.edu/courses/1246518/pages/what-is-an-agent?module_item_id=10564200).

Sometimes, particularly in the context of steering behavior these agents may be refered to as autonomous characters or Non-Player Characters (NPC).

### Agent-Based Modeling and Simulation

"An agent-based model (ABM) is one of a class of computational models for simulating the actions and interactions of autonomous agents (both individual or collective entities such as organizations or groups) with a view to assessing their effects on the system as a whole, ([Wikimedia Foundation, Inc., 2017c](https://en.wikipedia.org/wiki/Agent-based_model)).

### Types of Agent-Based Simulation
There are many types of agent-based simulation
* Social influence and opinion formation
* Coalition formation
* Collective intelligence
* Social networks
* Group dynamics
* Social cooperation
* Social norms
* Social conflict
* Financial markets
* Competition and cooperation between firms
* Micro-economic models
* Macro-economic models
* Organization and managerial decisions
* Migration
* Agglomeration and segregation
* Urban and regional development
* Traffic dynamics
* Crowd dynamics
* Systemic risks in socio-economic systems

([Source](https://webcourses.ucf.edu/courses/1246518/pages/agent-based-simulation-overview?module_item_id=10558346))

## Part 1: Steering Behaviors

### Background
To demonstrate my understanding of the problem. I have provided some background informaiton below.

#### Steering Behaviors Defined

*What are steering behaviors?*

In computer animaltion, *steering behaviors* can be defined as methematical formulas used to simulate "flocking" behvaiors similar to the movement of birds, schools of fish, and other groups of behavioral agents. Above, I introduced agent-based simulation. Steering behaviors can help program the behavioral aspects of agents in a way that allows for close-to-natural, improvized movement in an efficient way using simple forces (called *steering forces*; [Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)). Types of steering behaviors and forces will be described in more detail later in the present document and implemented using C++ programing in Visual Studio. While ther are many ways to program agent behvaior, in the present document I focus on a specific model called Boids Model.

Here is an [example](https://www.youtube.com/watch?v=tEGR6NN-cQc) of a similar project. This video shows how the agent(s) *should* move based on their steering behaviors.

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

#### Alternitives to Boids
Although not the focus of the present assignment, there are alteratives to the Boid Model for programming swarm, flocking, and herding behaviors. These include:
* Bees Algorithm ([Source](https://en.wikipedia.org/wiki/Bees_algorithm))
* Ant Colony Optimization Algorithms ([Source](https://en.wikipedia.org/wiki/Ant_colony_optimization_algorithms))

### 1.a) Compute Derivative Vector and Initial Values

 The "boids" or agents similate a "flight-like" pattern by taking incremental "steps" or moves ([Reynolds,1987](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)), modeled uing Euler's Method (which we also learned and integrated into HW 1; [Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)).

![](images/Euler.JPG?raw=true)

[Source](https://webcourses.ucf.edu/courses/1246518/pages/eulers-method?module_item_id=10526148)

To calculate Eulers method, we need to determine the *derivative* and the *initial value*. We will also need a *time step* to calculate Euler; however, this is provided for us in the based code. I believe the time step is located in the Agent.h file under member variables as *deltaT*. This is confirmed in the code given by Dr. Kider for *SIMAgent::UpdateState()* which I will adress later in this document.


#### Find the Derivative

To implement *SIMAgent::FindDeriv()* I first looked up some example code. I found [this resource](https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp) to use as a starting point. A group of students and I also went through this during study group on 4/13/2017. However, based on the informaiton provided in the original Readme.md file, I believe the code we collaborated on in the study group was incorrect (or at least partially incorrect). However, using the informaiton from the original Readme file, my agent did not move at all. I played around with it wrote it in the *order* it was presented in the original read me file rather than following it completely. This seemed to work.  This order was confirmed by [this Piazza post](https://webcourses.ucf.edu/courses/1246518/external_tools/11900). To view more informaiton about the code we tried please see the Agent.cpp file under *SIMAgent::FindDeriv()*. Here you can see the information and additional notes commented out.

Below are the derivative vectors implemented in my code.

	deriv[0] = state[2];
	deriv[1] = state[3];
	deriv[2] = input[0] / Mass;
	deriv[3] = input[1] / Inertia;

#### Determine the Initial Values

To implement *SIMAgent::InitValues()* I first looked up some example code. I found [this resource](https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp) to use as a starting point.

Below are the initial values implemented in my code.

	Kv0 = 10.0;
	Kp1 = -90.0;
	Kv1 = 40.0;
	KArrival = 0.03;
	KDeparture = 0.5;
	KNoise = 10.0;
	KWander = 8.0;
	KAvoid = 1.0;
	TAvoid = 20.0;
	RNeighborhood = 5000.0;
	KSeparate = 5000.0;
	KAlign = 5000.0;
	KCohesion = 5000.0;

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

![](images/steering_forces_seek_path.png?raw=true)

[Source](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)

Below is the code I implemented for *seek*.

	vec2 tmp;
	tmp = goal - GPos;
	tmp.Normalize();
	thetad = atan2(tmp[1],tmp[0]);
	vd = MaxVelocity;
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

Where *tmp* is the desired velocity to the new "goal" position, *thetad* is the desired orientation, and *vd* is the max velocity. The desired velocity is "the shortest path from the current position to the target" ([Kider, 2017c](https://github.com/hepcatjk/IDS6938-SimulationTechniques)). The velocity vector for seek is calculated as: velocity = normalize(target - position) x max_velocity, ([Bevilacqua, 2012a](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849)), which is why tmp is normalized in the code presented above. For *thetad* "we need to derive is the new angle the agent should be targeting, again we are using our basic trigonometric properties," ([Kider, 2017c](https://github.com/hepcatjk/IDS6938-SimulationTechniques)). The max velocity calculates how quickly the agent is moving ([Kider, 2017c](https://github.com/hepcatjk/IDS6938-SimulationTechniques)). Then the code should return the cartesian coordinates for the agent to go to ([Kider, 2017c](https://github.com/hepcatjk/IDS6938-SimulationTechniques)), which can be seen in the return statment.

To view the notes associated with this code, please view my edited Agent.cpp file. I summarized the C++ notes for readability. We went through this peice of code during study group on 4/13/2017.

#### [Flee](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616)

*Fleeing* behvaior is defined as "the agent attempts to steer away from a specified target," ([Kider, 2017b](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616)).

![](images/steering_forces_flee_path.png?raw=true)

[Source](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303)

Below is the code I implemented for *flee*.

	vec2 tmp;
	tmp = goal - GPos;
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	vd = MaxVelocity;
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

The code for flee is similar to the code for seek. However, to account for the opposite direction/orientation, I could add pi to thetad to achieve the new desired velocity, which can be denoted as  *thetad = thetad + M_PI*, ([Kider, 2017b](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616)). Alternativly, I could also switch the *GPos* and *goal* withing *tmp* instead of adding pi, ([Bevilacqua, 2012b](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303)). I tried both and it seems to work. I chose to use the second method as it was easier for me to understand.

To view the notes associated with this code, please view my edited Agent.cpp file. I summarized the C++ notes for readability. We went through this peice of code during study group on 4/13/2017.

#### [Arrival](https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664)

*Arrival* behavior is defined as "the agent attempts to steer towards a specified target and slows down when it gets close," ([Kider, 2017d](https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664)).

"The arrival behavior prevents the character from moving through the target. It makes the character slow down as it approaches the destination, eventually stopping at the target," ([Bevilacqua, 2012b](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303)). As seen in the figure below, the agent will approach the target similarly to the *seek* function presented above, once the agent get within a certian distance, it will slow until it reaches the target, ([Bevilacqua, 2012b](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303)).

![](images/arrival.png?raw=true)

[Source](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303)

Below is the code I implemented for *arrival*.

	vec2 tmp;
	tmp = goal - GPos;
	vd = tmp.Length()*KArrival;
	Truncate(vd, 0, MaxVelocity);
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. We also went through this during study group on 4/13/2017. However, I wasn't satisfied with *why* we chose to code it the way we discussed, so I started over. To make the agent slow when approaching the target, I've used the equations given to us by Dr. Kider ([Kider, 2017d](https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664)), which can be see in the "vd=abs(dist)*KArrival;" line. I additionally truncateed the velocity as recommended by Bevilacqua ([2012b](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303)). I chose the values within this based on a quote found in the Reynolds ([1987]((http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db)) paper: "it will not exceed a certain maximum speed . A minimum speed can also be specified but defaults to zero."

#### [Departure](https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664)

*Departure* behavior is defined as "the agent attempts to steer away from a specified target and slows down after a point," ([Kider, 2017d](https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664)). Similar to how flee is the opposite of seek, departure is the opposite of arrival.

Below is the code I implemented for *departure*.

	vec2 tmp;
	tmp = GPos-goal;
	vd = tmp.Length()*KArrival;
	Truncate(vd, 0, MaxVelocity);
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. We also went through this during study group on 4/13/2017. This code is different from arrival in that it uses *KDaprture* instead of *KArrival*. Also, I changed the *tmp* position similar to *flee* above.

#### [Wander](https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154)

*Wander* is defined as "the agent is moving around randomly," ([Kider, 2017e](https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154)).

There may be an instance where one may want non-player characters (NPCs) to "wander" about before recieving an action. This may occure in an an open field or within a building prior to an event that triggers a different type of behavior. In this instance I could use one of two different approaches. One is to utilize the seek funtion with randomness introduced ([Bevilacqua, 2012c](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624)). "The seek algorithm can be used to steer the agent. Imagine the agent is in the center of a circle, in the simplest case, towards random points on the circumference," ([Kider, 2017e](https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154)). However, this approach instructs the agent to again behave abruptly, moving in one direction and then immediatly turning ([Bevilacqua, 2012c](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624)). However, using another method which reduces this will allow me to be able to program more natural movement. This could be acieved by using small displacements each frame rate so that each frame has a slightly different angle, appearing as if the agent is moving slowly, ([Bevilacqua, 2012c](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624)).

![](images/wander_displacement_force.png?raw=true)

[Source](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-16243)

Below is the code I implemented for *wander*.

	vec2 tmp;
	float angle = float(rand() % 360) / 180.0 * M_PI;
	vd = MaxVelocity;
	thetad = angle;
	tmp = vec2(cos(thetad)*vd*KNoise, sin(thetad)*vd*KNoise)*KWander;
	return tmp;

To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. I tried many different approached to implement wander. I followed something the study group came up with on 4/13/2017 but it did make sense to me so I didnt want to use the code. I then tried another method I found on online ([Bevilacqua, 2012c](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624)). However, I wasn't able to fully work through this method in a way that worked in the code. Eventually, I just used the informaiton from webcourses stating "another way to implement this is to pick a random angle multiply some random noise (Knoise) to the x and y directions of the velocity, and multiply a damping term (KWander)," ([Kider, 2017e](https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154)).

#### [Avoid](https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154)
There are two different methods approached to program obstical avoidance, the *force field approach* and the *steer-to-avoid approach* ([Prinston, 2012](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf)).

**Force Field Approach**- In the force field approach obsticals are place within the environment. The obstacles are programmed to have a field of repulsion  and the closer the agent get to the field of repulsion the stronger the repulsion reaction, ([Prinston, 2012](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf)). However, this is limited in certain individual behaviors such as "wall following," ([Prinston, 2012](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf)).

**Steer-To-Avoid Approach**- In the steer-to-avoid approach the agent will acount for only the object in from of it. The edge of the obstical is used and the agent is directed to stay one boyd length away from the edge, ([Prinston, 2012](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf)).

![](images/avoid.png?raw=true)

[Source](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-collision-avoidance--gamedev-7777)

Below is the code I implemented for *avoid*.

	vec2 tmp;
	vec2 ahead;
	vec2 ahead2;

	ahead = GPos + v0.Normalize() * KAvoid;
	ahead2 = GPos + v0.Normalize() * KAvoid * 0.5;
	for (int i = 0; i < env->obstaclesNum; i++) {
		vec2 tmp; //create center point of obstacle
		tmp[0] = env->obstacles[i][0];
		tmp[1] = env->obstacles[i][1];

		float dist1 = (tmp - ahead).Length();
		float dist2 = (tmp - ahead2).Length();

		if (dist1 <= env->obstacles[i][2] || dist2 <= env->obstacles[i][2]) {

			thetad = thetad + TAvoid;
			ClampAngle(thetad);
			vd = MaxVelocity;
			return vec2(cos(thetad)*vd, sin(thetad)*vd);
		}
		else {
			return Arrival();
		}
	}
	thetad = atan2(tmp[1], tmp[0]);
	return tmp;
}

To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. I used the approach layed out by Bevilacqua [2012c](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-collision-avoidance--gamedev-7777) and got to "Calculating the Avoidance Force" before having to turn in the assignment. I don't believe the code works how I would like it to.

#### Other individual behaviors include :
* **Pursuit**- "following a target aiming to catch it," ([Bevilacqua, 2012d](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-pursuit-and-evade--gamedev-2946)).
* **Evade** - "Instead of seeking the target's future position, in the evade behavior the character will flee that position," ([Bevilacqua, 2012d](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-pursuit-and-evade--gamedev-2946)).

Pursuit| Evade
-------- | --------
![](images/pursuit2.png?raw=true)|![](images/evade.png?raw=true)

([Source](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-pursuit-and-evade--gamedev-2946))

More individual behaviors ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/); [Prinston, 2012](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf)):
* Containment
* Wall Following
* Path Following
* Offset Pursuit
* Flow Following
* Unaligned Collision Avoidance

Wall Following and Containment| Path Following
-------- | --------
![](images/wall.png?raw=true)|![](images/path.png?raw=true)

([Source](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf))

Offset Pursuit| Flow Following| Unaligned Collision Avoidance
-------- | -------- | --------
![](images/off.png?raw=true)|![](images/flowfield.png?raw=true) |![](images/unaligned.png?raw=true)

([Source](http://www.red3d.com/cwr/steer/gdc99/))

*It is important to note here that Reynolds ([1999](http://www.red3d.com/cwr/steer/gdc99/)) uses a combination of wall following and containment for obstical avoidance above. In general it was a bit confusing as many sources called some of the more "complex" behaviors different things*

*Additionally, You will see some of these behaviors later in the Anylogic Models*

### 1.c) Group Behaviors:
Note: Each section title is linked to the corresponding WebCourses URL.
#### [Seperation](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)

*Separation* is defined as "steer to avoid crowding local flockmates," ([Kider, 2017f](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)).

Separation is used to allow agents to disperse and avoid crowding ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)). To implement seperation one can use two different methods for determining thecloses agent: (1) to use an exhaustive search to find the sum of all the other agents' positions, or (2) to use a local search to find the position of the closest neighbor and comparing that to the characters position ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)). Then I would apply a repulsion force by "subtracting the position of our character and the nearby character, normalizing, and then applying a 1/r weighting," ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)). Then I return the coordinates. This can be seen in the code below

![](images/separation.gif?raw=true)

[Source](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)

Below is the code I implemented for *seperation*.

	vec2 tmp;
	vec2 V = vec2(0.0, 0.0);
	float pX = 0.0;
	float pY = 0.0;

	vec2 pV;
	vec2 VSep;

	for (int i = 0; i < agents.size(); i++) //call agent in the system
	{
		pX = GPos[0] - agents[i]->GPos[0];
		pY = GPos[1] - agents[i]->GPos[1];
		pV = vec2(pX, pY);
		if (((pX != 0.0) || (pY != 0.0)) && (pV.Length() < RNeighborhood))
		{
			V[0] += (pX / pV.Length()); //1/r
			V[1] += (pY / pV.Length()); //1/r
		}
	}
	VSep = KSeparate * V;
	thetad = atan2(VSep[1], VSep[0]);
	vd = VSep.Length();
	Truncate(vd, 0, MaxVelocity);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. I tried two different methods to implement seperation. We went over these two different methods in the Study Group on 4/24/2017. I altered the code we went over after the study group because it didnt quite work the way I wanted it to. To find the other characters we used the global/exhaustive search method (which can also be seen in cohesion and alignment). Out of the two approaches we tried, I found that using a method which utilized X and Y seperatly rather than treating it like a vector worked better. I ended up working on seperation, cohesion, and alignment simultaneously. It was easiest to get alignment and then work on the other two.


#### [Cohesion](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)

*Cohesion* can be defined as making the agents "steer to move toward the average position of local flockmates," ([Kider, 2017f](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)).

Cohesion is used to group the characters ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)). To implement cohesion, one can use one of the same two methods noted in seperation for finding the position of the other agents ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)). Then use the seek function as a base to have all of the characters group toward the average position ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)).

![](images/cohesion.gif?raw=true)

[Source](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)

Below is the code I implemented for *cohesion*.

    	vec2 tmp;
	vec2 sum;
	for (int i = 0; i< agents.size(); i++) {
		tmp = agents[i]->GPos - GPos;
		if (tmp.Length() < RNeighborhood) {
			sum += tmp;
		}
	}
	sum = ((sum / agents.size()) - GPos);
	tmp = goal - GPos;
	vd = tmp.Length();
	Truncate(vd, 0, MaxVelocity);
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. We went over cohesion in the Study Group on 4/24/2017. I altered the code we went over after the study group because it didnt quite work the way I wanted it to.

#### [Alignment](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)

*Alignment* is defined as making the agents "steer towards the average heading of local flockmates," ([Kider, 2017f](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)).

Alignment is used to orient (heading) all of the agents toward the same direction ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)). To find the other characters I can again use one of the two methods described in seperation. Then I should average the velocity of all the other characters to figure out the "desired velocity," which will steer the characters all in the same direction ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)).

![](images/alignment.gif?raw=true)

[Source](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478)

Below is the code I implemented for *allignment*.

	vec2 tmp;
	vec2 sum;
	for (int i = 0; i < agents.size(); i++) {
		tmp = agents[i]->GPos - GPos;
		if (tmp.Length() < RNeighborhood)
			sum = agents[i]->v0.Normalize();
	}
	tmp = goal - GPos;
	thetad = atan2(tmp[1], tmp[0]);
	vd = tmp.Length()*KArrival;
	Truncate(vd, 0, MaxVelocity);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. We went over alignment in the Study Group on 4/24/2017. I altered the code we went over after the study group because it didnt quite work the way I wanted it to.

#### [Flocking](https://webcourses.ucf.edu/courses/1246518/pages/flocking-and-leader-following?module_item_id=10573471)

Below is the code I implemented for *flocking*.

    vec2 tmp;
	vec2 s = Separation();
	vec2 a = Alignment();
	vec2 c = Cohesion();
	return tmp;

#### [Leader Following](https://webcourses.ucf.edu/courses/1246518/pages/flocking-and-leader-following?![](images/alignment.gif?raw=true)

*Leader Following* can be defined as "one or more [characters following] another moving characters designated as the leader," ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)).


Typically the agents need to stay clear of the leader's path without crowding or getting in front of the leader ([Reynolds, 1999](http://www.red3d.com/cwr/steer/gdc99/)). Additionally, these follwer dont want to bump into each other as well.

![](images/leader.png?raw=true)

[Source](http://www.red3d.com/cwr/steer/gdc99/)

Below is the code I implemented for *leader following*.

	vec2 tmp;
	if (GPos == agents[0]->GPos)
	{
		return Seek();
	}
	else
	{
		vec2 V = vec2(0.0, 0.0);
		float pX = 0.0;
		float pY = 0.0;
		vec2 pV;

		pX = agents[0]->GPos[0];
		pY = agents[0]->GPos[1];
		pV = vec2(pX, pY);

		tmp = pV - GPos;
		vd = tmp.Length()*KArrival;
		Truncate(vd, 0, MaxVelocity);
		tmp.Normalize();
		thetad = atan2(tmp[1], tmp[0]);
		return vec2(cos(thetad)*vd, sin(thetad)*vd);

		tmp = agents[0]->GPos - GPos;
		vec2 s = Separation();
	}
	return tmp;

To view the notes associated with this code, please view the Agent.cpp file. I ommitted the notes for readability. We went over alignment in the Study Group on 4/24/2017. I altered the code we went over after the study group becuse the leader following did not work at all using the code from the study group. To try and rework the code I used Shijingliu (2014) as an example. I used this information to figure out how to designate the leader. Then I coded the leader to seak the target. I then coded the remaining agents to arrive at the leader (using the leader's X and Y coordinates) and then follow behing the leader by one body length. Then I called the separation functions as instructed by Kider ([2017g](https://webcourses.ucf.edu/courses/1246518/pages/flocking-and-leader-following?module_item_id=10573471)). However, I dont think the separation function is working in the code.


#### Other Group Behaviors Include:
* **Queueing**- In this instance, is defined as "is the process of standing in line, forming a row of characters that are patiently waiting to arrive somewhere," [Bevilacqua, 2012e](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-queue--gamedev-14365).


## Part 2 - Simulating a Simple Pedestrian Flow


### 2.a) Follow the Anylogic Example for the [Subway Entrance Example](https://help.anylogic.com/index.jsp?topic=/com.xj.anylogic.help/html/_PL/tutorial/Subway_Entrance.html)

<a href="http://www.youtube.com/watch?feature=player_embedded&v=8ESffmzlObc" target="_blank"><img src="http://img.youtube.com/vi/8ESffmzlObc/0.jpg" alt="Anylogic" width="850" height="490" border="1" /></a>
^^click me^^ *If that doesn't work click [here](https://www.youtube.com/watch?v=8ESffmzlObc)*

### 2.b) Create a Maze

<a href="http://www.youtube.com/watch?feature=player_embedded&v=dT9LYcIQwr0" target="_blank"><img src="http://img.youtube.com/vi/dT9LYcIQwr0/0.jpg" alt="Anylogic" width="850" height="490" border="1" /></a>
^^click me^^ *If that doesn't work click [here](https://www.youtube.com/watch?v=dT9LYcIQwr0)*

#### A Little Bit of Fun!

**TARDIS MAZE PART 1**

<a href="http://www.youtube.com/watch?feature=player_embedded&v=LXLwLjtsjPA" target="_blank"><img src="http://img.youtube.com/vi/LXLwLjtsjPA/0.jpg" alt="Anylogic" width="850" height="490" border="1" /></a>
^^click me^^ *If that doesn't work click [here](https://www.youtube.com/watch?v=LXLwLjtsjPA)*

**TARDIS MAZE PART 2**

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Qs1yJ3Jczt4" target="_blank"><img src="http://img.youtube.com/vi/Qs1yJ3Jczt4/0.jpg" alt="Anylogic" width="850" height="490" border="1" /></a>
^^click me^^ *If that doesn't work click [here](https://www.youtube.com/watch?v=Qs1yJ3Jczt4)*

*Here is where some of the boids behaviors can be seen*

### 2.c) Model and Analyze a Building/Floor/Outdoor Space/Stadium on Campus

**Model:** UCF Library Main Floor

**Research Question:** If students enter the Library at a discrete uniform random interarrival rate and there is about a 1/3 chance that students will get coffee before they study, how many students will get coffee at Java City?

![](images/library.png?raw=true)

[Source](https://library.ucf.edu/maps/)

**UCF Library PART 1**

<a href="http://www.youtube.com/watch?feature=player_embedded&v=LXLwLjtsjPA" target="_blank"><img src="http://img.youtube.com/vi/LXLwLjtsjPA/0.jpg" alt="Anylogic" width="850" height="490" border="1" /></a>
^^click me^^ *If that doesn't work click [here](https://www.youtube.com/watch?v=LXLwLjtsjPA)*

**UCF Library PART 2**

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Qs1yJ3Jczt4" target="_blank"><img src="http://img.youtube.com/vi/Qs1yJ3Jczt4/0.jpg" alt="Anylogic" width="850" height="490" border="1" /></a>
^^click me^^ *If that doesn't work click [here](https://www.youtube.com/watch?v=Qs1yJ3Jczt4)*


## Future Work

* I found a [link](* https://runthemodel.com/models/204/) that specifically calls out Boids in AnyLogic. I wasnt able to run the model they posted because I didnt have the right software but if given more time I would have liked to see how this source implemented Boids and build that into my anylogic model.

* I would also have liked to compare multiple runs but in order to use this feature I would either need to output multple instances and save them as seperate files (I would if I had more time to finish) or to purchase the professional version of AnyLogic

* I would like to study the "control" code a bit more. It was unclear to me how that fit in. I believe it is to make sure the change in movement is smooth

* I would have like to researched more about the varying types of agent-based simulation and compared them here

## References

### Literature and Online Sources

*Citations are numbered by the order they were put in the document rather than the order they appear in.*

* Bevilacqua, F. (2012a). [Understanding Steering Behaviors: Seek](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849). Retrived from https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-seek--gamedev-849

* Bevilacqua, F. (2012b). [Understanding Steering Behaviors: Flee and Arrival](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303). Retrived from https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-flee-and-arrival--gamedev-1303

* Bevilacqua, F. (2012c). [Understanding Steering Behaviors: Wander](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624). Retrived from https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624

* Bevilacqua, F. (2012d). [Understanding Steering Behaviors: Pursuit and Evade](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-pursuit-and-evade--gamedev-2946). Retrived from https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-pursuit-and-evade--gamedev-2946

* Bevilacqua, F. (2012e). [Understanding Steering Behaviors: Queue](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-queue--gamedev-14365). Retrived from https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-queue--gamedev-14365

* Bevilacqua, F. (2012f). [Understanding Steering Behaviors: Leader Following](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-leader-following--gamedev-10810). Retrived from https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-leader-following--gamedev-10810

* Bevilacqua, F. (2012g). [Understanding Steering Behaviors: Collision Avoidance](https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-collision-avoidance--gamedev-7777). Retrived from https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-collision-avoidance--gamedev-7777

* Flemhead-d3lc535 (n.d.). [A Maze](http://pre13.deviantart.net/2b52/th/pre/i/2011/188/3/e/a_maze_____by_flemhead-d3lc535.jpg). Retrived from http://pre13.deviantart.net/2b52/th/pre/i/2011/188/3/e/a_maze_____by_flemhead-d3lc535.jpg

* Kider, J. (2017a). [Boids](https://webcourses.ucf.edu/courses/1246518/pages/boids?module_item_id=10564246) [Webcourse Module]. Retrived from https://webcourses.ucf.edu/courses/1246518/pages/boids?module_item_id=10564246

* Kider, J. (2017b). [Seek and Flee](https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616) [Webcourses Module]. Retrived from https://webcourses.ucf.edu/courses/1246518/pages/seek-and-flee?module_item_id=10571616

* Kider, J. (2017c). [Agent.cpp](https://github.com/hepcatjk/IDS6938-SimulationTechniques). Retrived from https://github.com/hepcatjk/IDS6938-SimulationTechniques

* Kider, J. (2017d). [Arrival and Departure](https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664) [Webcourses Module]. Retrived from https://webcourses.ucf.edu/courses/1246518/pages/arrival-and-departure?module_item_id=10571664

* Kider, J. (2017e). [Wander and Avoid](https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154) [Webcourses Module]. Retrived from https:https://webcourses.ucf.edu/courses/1246518/pages/wander-and-avoid?module_item_id=10573154

* Kider, J. (2017f). [Separation, Cohesion, and Alignment](https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478) [Webcourses Module]. Retrived from https://webcourses.ucf.edu/courses/1246518/pages/separation-cohesion-and-alignment?module_item_id=10573478

* Kider, J. (2017g). [Flocking and Leader Following](https://webcourses.ucf.edu/courses/1246518/pages/flocking-and-leader-following?module_item_id=10573471) [Webcourses Module]. Retrived from https://webcourses.ucf.edu/courses/1246518/pages/flocking-and-leader-following?module_item_id=10573471

* Prinston (2012). [Boids COS 426](http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf). Retrived from http://www.cs.princeton.edu/courses/archive/spr12/cos426/notes/cos426_s12_lecture20_boids.pdf

* Reynolds, C. W. (1987). [Flocks, heards, and schools: A distributed behvaioral model](http://delivery.acm.org/10.1145/40000/37406/p25-reynolds.pdf?ip=132.170.253.255&id=37406&acc=ACTIVE%20SERVICE&key=5CC3CBFF4617FD07%2E2826F4AA9CF74935%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=752717236&CFTOKEN=59149052&__acm__=1492607460_82307315c3d46cd16890ecb2213f02db). *Computer Graphics, 21*(4), p. 25-34.

* Reynolds, C. W. (1999). [Steering Behaviors For Autonomous Characters](http://www.red3d.com/cwr/steer/gdc99/). Retrived from http://www.red3d.com/cwr/steer/gdc99/

* Shijingliu (2014). [Agent.cpp](https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp). Retrived at https://github.com/shijingliu/CIS-562-Behavioral-Animation/blob/master/Agent.cpp.

* UCF Libraries (2017). [Maps and Addressess](https://library.ucf.edu/maps/). Retrived from https://library.ucf.edu/maps/

* Wikimedia Foundation, Inc., (2017a).[Velocity](https://en.wikipedia.org/wiki/Velocity). Retrived from https://en.wikipedia.org/wiki/Velocity

* Wikimedia Foundation, Inc., (2017b). [Boids](https://en.wikipedia.org/wiki/Boids). Retrived from https://en.wikipedia.org/wiki/Boids

* Wikimedia Foundation, Inc., (2017c). [Agent-based model](https://en.wikipedia.org/wiki/Agent-based_model). Retrived from https://en.wikipedia.org/wiki/Agent-based_model

### Study Group
*Overall, I think the study groups are helpful to get a good head start on the different parts of the code but I defintly spent a good amount of time on the code myself to make sure it worked properly.*

* 4/13/2017
*Note: I'm not 100% sure who all was in this group since I attended via skype (audio only). These we just the voices I could hear.*
	* Keith MacArthur
	* Sarah Matthews
	* Roberto Cabrera
* 4/24/2017
	* Keith MacArthur
	* Sarah Matthews
	* Charlie Timm

## Further Reading

* http://www.red3d.com/cwr/steer/
* http://www.red3d.com/cwr/boids/
* Different method for Avoid - http://www.red3d.com/cwr/nobump/nobump.html

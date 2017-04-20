#Homework 1 : The Jello Cube (Continuous Simulation Assignment)
## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)
###Submitted By Rebecca Leis
I plan to use TWO of my "extra days" to finish up this assignment.
Note: Images and code were create at various points in the project and I updated sections as I went along. It does not progress in chronological order.
##PART 1- Numerical Analysis of Integration Functions
###(a) Solve for the exact symbolic (analytical)solution.
> ![](images/Part A.png?raw=true)

### (b) After step (a) you have the values for the df and exact functions. Translate the mathematical formulas you now have into the df and exact functions.
> ![](images/Part B-v3.png?raw=true)
Changed the “exp(“ to “pow(M_E,” based on another students suggestion; however this didn’t seem to make any difference, so I changed it back. I looked it up. "exp(" and "pow(M_E," seems to be the same thing:
* http://www.dreamincode.net/forums/topic/19674-using-m-e/
* http://www.cplusplus.com/reference/cmath/exp/

> Replaced all of the single numbers (e.g., “1”) with a decimal (e.g., “1.0”) and that seemed to give me the “correct values” based on the Piazza Posts

###(c) Run three numerical integration solutions: RK1, RK2, and RK4 to generate the numerical and exact values. To start use h = 0.1, for x =< 0.0,10.0 >. (Hint: this produces 100 values for each solution.) Graph the results of RK1, RK2, and RK4 and the exact solution. (Use whatever approach you like to graph this data: R, Python, Matlab, Excel - you should produce a graph with 4 curves.)

> I printed the values into Excel
![](images/Part C-Excel-v3.png?raw=true)
And Created the graph with the results from RK1, RK2, RK4 and the Exact Solution
![](images/Part C-Graph-v2.png?raw=true)
Below is a table of the values I printed as an .csv file in Excel

| X | RK1  | RK2 | RK4 | Exact |
| -------------| ------------- | ------------- | ------------- | ------------- |
|0	|0	|0	|0	|0	|
|0.1	|0.5	|0.5090369272	|0.5040147599	|0.5040062116	|
|0.2	|0.9860882804	|0.9418917554	|0.9299833736	|0.9299692608	|
|0.3	|1.336761843	|1.178280127	|1.158938591	|1.158923832	|
|0.4	|1.453584287	|1.136380907	|1.110627992	|1.110618385	|
|0.5	|1.28927035	|0.7981592984	|0.7684526188	|0.7684534442	|
|0.6	|0.8654303303	|0.2207680347	|0.1904774691	|0.1904920858	|
|0.7	|0.2742737135	|-0.470402004	|-0.4978138899	|-0.497785095	|
|0.8	|-0.337857308	|-1.107144704	|-1.129056656	|-1.129016654	|
|0.9	|-0.802753054	|-1.517667616	|-1.533117725	|-1.533072395	|
|1	|-0.971671551	|-1.570878628	|-1.581041974	|-1.580998849	|
|...	|...	|...	|...	|...	|
|9.1	|1385.328763	|176.2233273	|94.44915487	|94.49905918	|
|9.2	|1521.647688	|180.3673069	|89.65808285	|89.71379662	|
|9.3	|1647.829303	|161.3606021	|61.03567726	|61.09819136	|
|9.4	|1767.116099	|124.1582495	|13.51631062	|13.58651544	|
|9.5	|1888.596144	|79.22459545	|-42.53333378	|-42.45472598	|
|9.6	|2025.825999	|40.4187988	|-93.43846738	|-93.35094466	|
|9.7	|2194.184043	|21.77807556	|-125.4239703	|-125.3271744	|
|9.8	|2407.512568	|33.91946812	|-128.1856199	|-128.0792336	|
|9.9	|2674.851039	|80.95594681	|-97.93441991	|-97.81800842	|
|10	|2998.124017	|158.7831645	|-39.0670402	|-38.93988091	|


### (d) Plot the error percentages for RK1, RK2, and RK4 in another graph. Remeber the error is deﬁned as : %error = |exact−approx|/exact .
> ![](images/Part D-graph.png?raw=true)


### (e) Vary the step size h = n where you deﬁne three n values for x =< 0.0,10.0 >. Plot the results just for RK4 with 3 different n values (with the exact solution). Plot the error rate.

####h=1.0
> ![](images/Part E1.png?raw=true) ![](images/Part E1-Graph.png?raw=true)

####h=0.5

> ![](images/Part E2.png?raw=true) ![](images/Part E2-Graph.png?raw=true)

####h=0.15
> ![](images/Part E3.png?raw=true) ![](images/Part E3-Graph.png?raw=true)
Here is the table for h=0.15 as only some values can be seen in the picture displayed.

|	x	|	y (RK4)	|	EXACT	|	%Err(RK4)	|
|	----	|	----------	|	----------	|	------	|
|	0	|	0	|	0	|	0	|
|	0.15	|	0.734787217	|	0.734727616	|	8.11E-05	|
|	0.3	|	1.158996952	|	1.158923832	|	6.31E-05	|
|	0.45	|	0.974420555	|	0.974398739	|	2.24E-05	|
|	0.6	|	0.190413344	|	0.190492086	|	0.00041336	|
|	0.75	|	-0.831799127	|	-0.831616812	|	-0.00021923	|
|	0.9	|	-1.533306552	|	-1.533072395	|	-0.00015274	|
|	1.1	|	-1.452195171	|	-1.451993415	|	-0.00013895	|
|	1.2	|	-0.509225806	|	-0.509128232	|	-0.00019165	|
|	1.3	|	0.883922199	|	0.883901402	|	2.35E-05	|
|	1.5	|	1.985822773	|	1.985745966	|	3.87E-05	|
|	1.6	|	2.105289201	|	2.105272801	|	7.79E-06	|
|	1.8	|	1.01349091	|	1.013647908	|	0.00015488	|
|	1.9	|	-0.847474288	|	-0.847098809	|	-0.00044325	|
|...	|...	|...	|...	|
|	9	|	76.35547385	|	76.59589429	|	0.0031388	|
|	9.2	|	94.87210784	|	95.15311457	|	0.0029532	|
|	9.3	|	60.76499098	|	61.09819136	|	0.0054535	|
|	9.5	|	-14.57458182	|	-14.17881262	|	-0.027913	|
|	9.6	|	-93.81659568	|	-93.35094466	|	-0.0049882	|
|	9.8	|	-131.3140033	|	-130.7738385	|	-0.0041305	|
|	9.9	|	-98.43748138	|	-97.81800842	|	-0.0063329	|




### (f) Analyze you results: (1) Describe how varying the integration method changes the accuracy. (2) What happens as you increase the x value to the accuracy. (3) How does varying the step size effect the accuracy. (4) Which method is the most accurate and why (in particular explain what is taken to account in the solution).

1. Varying the integration method changes the accuracy of the output. RK1 (Euler)ia less accurate but less demanding computationally; whereass RK4 is more accurate but more demanding computatonally. Specifically, Euler is less stable and while less demanding cannot be considered "efficient" as it does not provide a good trade off between stepsize and accuract/stability (e.g., it still costs more per step; Witkin & Baraff, 1997).

2.  As X increases a wave patters emerges. Each waves seem to extend farther in both directions (difference between RK4 and the exact) the larger X becomes. Meaning that the percent error increases as X increases. 

3. As the step size becomes smaller, the more values are outputted by the program. These additional values allow the visual representation to show a more accurate curvature/variation of the lines. Although RK4 is the only integration method represented here, in the RK1 (Euler) integration "[s]hrinking the stepsize will slow the rate of this outward drift, but never eliminate it," (Witkin & Baraff, 1997).

4. For the present project, the most accurate solution would use RK4 menthods, with a larger X, with a small step size (e.g., Taylor Series). However, because this combination would output the most values, it can be computationally expensive. Note: In reality adaptive stepsizing (which varies the h) would be most accurate (Witkin & Baraff, 1997), but is outside the scope of this project.

## PART 2-Programming a Jello Cube
### Forward Euler, midpoint integration, and RK4
#####Euler Integration Code (derrived from RK4 and Mid-Point Code)
> ![](images/EulerCode1.png?raw=true)

#####Midpoint Integration Code (derrived from RK4 code)
> ![](images/MidpointCodeP1.1.png?raw=true) ![](images/MidpointCodeP2.1.png?raw=true)

#####RK4 Integration Code (Code provided by Dr. Kider)
> ![](images/RK4Code1.png?raw=true)
>
>There is additional code after this but since Dr. Kider provided it, I will not provide additional pictures for readability.

### Particle forces other than gravity
> ![](images/Compute Forces.png?raw=true) ![](images/UpdateSprings.png?raw=true)

### Collision and penetration detection
> ![](images/Check for Collisions1.png?raw=true)![](images/Floor Intersection1.png?raw=true)


### Collision and penetration response
> This is the ResolveContacts Code I had for before I integrated the CylinderIntersection
> ![](images/ResolveContacts.png?raw=true)
> This is the ResolveContacts Code I implemented after Cylinder Intersection
> ![](images/ResolveContactsBounce.png?raw=true)
> [Here is a video of what happened after implementing this](https://youtu.be/Z3cjhLjQXZ8)
> ![](images/ResolveCollisions.png?raw=true)

### Extra springs
#####Structural Springs (given by Dr. Kider via Piazza)
> ![](images/StructuralSprings.png?raw=true)

#####Bend Springs (edited using information provided by Dr. Kider via Piazza)
> ![](images/BendSprings.png?raw=true)
While most of this is commented out. I did play around with include and disclusing various bend springs. It seems like the more I added the more destabalized the jello cube became, so I chose to comment out a large portion. I just wanted to include it so you could see what I had experimented with.

#####Shear Springs (edited using the information provided by Dr. Kider via Piazza and sample code found online-see references)
> ![](images/ShearSprings.png?raw=true)
These are additional shear spring combinations I played around with. As will the bend springs, when I added more, the cube became more unstable, eventually exploding on itself.
> ![](images/ShearSprings E1.png?raw=true) ![](images/ShearSprings E2.png?raw=true) ![](images/ShearSprings E3.png?raw=true)

### Implementing 2 features on the extra features list
####(5 points) Create a movie of your jello cube environment, upload the video to youtube and link it in your assignment writeup.

Here is my Jello Cube Environment without the Cylinders:

#####[Stable](https://www.youtube.com/watch?v=CrrJiNLn4IQ)-Cick me!
> Note: This video is short and I would rather a little more bouncy to my cube
Here are the spring constants for this part:
![](images/Spring_Force_ValuesStable-ish.png?raw=true)

####(5 points) Create a movie of your jello cube that clearly explores the differences between integration types and spring stiffnesses, upload the video to youtube and link it in your assignment writeup.

#####[TipToe](https://www.youtube.com/watch?v=kbXBPWFoXRI)-Cick me!
> This is when I started playing around so I didnt save the constant values

#####[Water-like](https://youtu.be/Q5o4UmKpa4k)-Cick me!

> Note: this looks similar to the tiptoe but the top is a little more wavy
Here are the spring constants for this part:
![](images/Spring_Force_ValuesWater-ish.png?raw=true)

#####[Melting](https://youtu.be/iEbf36ehUyk)-Cick me!

> Here are the spring constants for this part:
> 
 ![](images/Spring_Force_ValuesMelting.png?raw=true)

#####[Wibbly Wobbly (I wish I made this blue)](https://www.youtube.com/watch?v=zKdjrBgpvds)-Cick me!
>  ![](images/WIbblyWobbly1.png?raw=true)

#####[10x10 and 4x4](https://www.youtube.com/watch?v=6_8mkzSrVzw)-Cick me!

#####[Liftoff](https://www.youtube.com/watch?v=KjZUbxwe9Vc)-Cick me!
>  ![](images/Lift-off.png?raw=true)

#####[Mid-point Integration](https://youtu.be/6gNyALFMLHQ)-Cick me!

> Note: I had added the Cylinders.xml file during this video but used the same spring constants as that of my "stable" video above.


## PART 3-Written Questions

###1) What is the effect of the Ks and Kd parameters on the jello?
> The Ks and the Kd are spring force constants. In this instance there are Structural, Shear, Bend, and Penalty forces. Attachment Ks and Kd didnt seem to do anything so I took them out. Ks is the elastic force and the Kd is the dampening force. Ks values tend to be in the thousands, whereas the Kd values tend ot be below 10. A good balance of spring constants is necessary otherwise the cube will destabalize. Specifically, for Kd the lower you set it (e.g., 2.0) the slower it goes/more damping, the higher (e.g., 8.0) the faster/less damping. At one point my cube fell very slowly when I began to implement the assignment and this is why. My Ks were set at 0.0 when I started to figure out the spring equations. Further, It also looks like Ks makes it bouncier/more elastic if its set lower (e.g., 1000) and stiffer if set higher (e.g., 3000).

###2) What are the beneﬁts and the drawbacks of the collision system used here? What are some different ways in which it could be improved? 
> This collision system is not truely accurate. Like the particles themselves, the collision formulas are approximations. That is why you have to create an collision detla/threshold. However, this also keeps the computation power low (in comparison). We could add accuracy by adding addional collision conditions/checks. For instance, with the cylinders, I could add additional checks with the sides and the angles of the cylinders rather than just head on. 

###3) What are some example systems you could model with Mass-spring simulations? Explain how you would you construct the model.
> You could build hair, grass, fur, cloth, water/fluids, fireworks, fire, and deformable shapes(e.g.,bouncy ball).The [Webcourse Modules](https://webcourses.ucf.edu/courses/1246518/pages/mass-spring-systems-in-practice?module_item_id=10539155) detail information on how to creat these types of systems. For example hair is a line of particles with similar Structural, Shear and Bend spring forces.

###4) Does the jello behave realistically? What integration method did you choose to make the Jello stable?
> It depends on the integration method and the spring constants chosen. I was able to stabalize my cube and get a to wiggle a little and a lot. I played around with the constants for quite a bit. However, I played mostly with the RK4 integration method as it seems to stay the most stable and remained the most accurate representaiton. This follows along with the answer given in Part 1f, Question number 4. I imagine that if there were a higher integration method [(e.g., 5th Order/Crackle, 6th order/Pop).](https://webcourses.ucf.edu/courses/1246518/pages/derivatives-of-position?module_item_id=10531384)

###5) How would you model and simulate water (in terms of a continuous simulation)?
> For water-like systems I would used a 3D System. Using a variation of Structural, Bend, and Shear Springs, you can create a water-like ripple (see above for an example of this on the jello cube). Generally this is done using lower spring/elastic constant values, and larger damping constants.
> Here is an example of a ["blue water cube"](https://www.youtube.com/watch?v=ZBs51SnkYIM) and the code I used to produce it:
> 
> ![](images/Blue Water Cube Code.png?raw=true) ![](images/BlueWaterCubeCode 2.png?raw=true)


##Extra Credit
###Multiple Jello cubes interacting
Trying to get multiple Jello Cubes in the video: [3 Jello Cubes Bouncing](https://www.youtube.com/watch?v=RS3O7yyD6mw&edit=vd) <-- Click Me!

Trying to get the Jello cubes to interact with cyliners: [3 Jello Cubes Not Stable](https://www.youtube.com/watch?v=_LWyBnCZpdc&edit=vd) <-- Click Me!

Playing with the number on bend spring forces: [Fly Away](https://youtu.be/wr6mslKDApA)<-- Click Me!

Three cubes somewhat stable: [Contact](https://www.youtube.com/watch?v=xKDj9OjOfHI&edit=vd)<-- Click Me!




##Extra Features Not in Extra Credit
####Youtube Video Directly in Readmefile

> <a href="http://www.youtube.com/watch?feature=player_embedded&v=6gNyALFMLHQ" target="_blank"><img src="http://img.youtube.com/vi/6gNyALFMLHQ/0.jpg" alt="Midpoint" width="240" height="180" border="10" /></a>
> 
Ultamatly I didnt want to put all of my videos in my read Me file like this becuse it still takes you to an outside link rather than playing the video in the readmefile, which is what I thought it would do. For readability I kept them out.

####Changing Cube Color
#####Black Cube
> ![](images/Black Cube1.png?raw=true) ![](images/BlackMesh Code.png?raw=true)
> Using the colors already in the JelloMesh.cpp file I played around and created a Black cube

#####Purple Cube
> ![](images/Purple Cube.png?raw=true) ![](images/PurpleCube Code.png?raw=true)
>
>Then I added an additional color to the JelloMesh::DrawMesh section. I used a combination of the Red, Green, Blue, Alpha (RGBA)Values to get purple (my favorite Color!). Then I shared my tips on the Google Hangouts Virtual Office Hours



## References
####Texts:

* Witkin, A. & Baraff, D. (1997). Physically based modeling: Principles and practice differential equation basics. Retrived from https://webcourses.ucf.edu/courses/1246518/files/60622625?module_item_id=10531352


####Website Assistance:

* https://github.com/mriveralee/hair-simulation/blob/master/Jello%20Simulation/JelloSim_basecode/JelloSim/jelloMesh.cpp Note: used this as a reference point. Mostly during the shear spring integration and the cylider intersection.
* http://www.dreamincode.net/forums/topic/19674-using-m-e/
* http://www.cplusplus.com/reference/cmath/exp/
* https://www.w3schools.com/cssref/css_colors_legal.asp Note:this was for the color help
* Webcourse Modules


####Class/Classmate/Webcourse Assistance:

* I worked with Karla most frequently. 
* I occationally worked with Oliva, Joe W., Ravi, Sarah, Cintya, and Ashley via study group sessions.
* I recieved help from the Google Hangouts Virtual Office Hours.
* I also utilized the Piazza posts often.
* Recieved outside assistance on rebuilding my project when it would not load properly for an outside source (C++ expert-Tavis Clements) Note: Tavis Clements did not actually help me generate code.
* Dr. Kider's assistance helped form this assignment as well.




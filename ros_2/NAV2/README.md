# Learning the Nav 2 systems
Treat the whole NAV 2 as one big Node, kinda like with subnodes (plugins)

When the NAV2 node recieves nav_goal, the global planner' createPlan will be called.

But how to give a velocity to the controller?

When does global planner call local planner? Perhaps i just set what planner is the local planner, then the NAV node will decvide when to call the local planner.

So now how do i deal with giving the planner the accurate current position. And giving a blkankcost map while allowing everything to work...hmmm

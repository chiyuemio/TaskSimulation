**A task scheduling simulator**

We implement a simple scheduler based on weakly hard scheduling method to simulate the scheduling process of multiple tasks on a single processor. The weakly hard scheduling model serves as a method for characterizing systems that can withstand certain deadline misses, which introduces (m,k) constraint to describe a task.

**(m,k) constraint**: no more than 𝑚 deadline misses must occur for any k consecutive activations of the task.

And we implemented the scheduler using the job-continue policy, which means the job will continue executing until its completion even if its deadline is missed.


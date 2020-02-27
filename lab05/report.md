# EECS 560 - Lab 5 Report
* Name: Jace Kline
* KUID: 2881618

## Question Responses
### Question 1 - Comparison Between Quadratic Probing and Double Hashing
Upon repeatedly generating the build time statistics of both the quadratic and double-hashing hash tables, there are two clear patterns that can be observed acress the multiple runs:
1. The build time of the quadratic probing table is consistently less for all input sizes than the build time for the double-hashing table. My hypothesis for this trend is that the chosen R-value of 773 (the alternative prime number less than m) is in some way not optimal for the hash table. Additionally, the collision function employed in the double-hashing table requires a greater number of computations. When considering hundreds of thousands of insertions (and therefore collision function calls), the extra complexity of the collision function in the double-hashing case could add up and create non-negligible differences between the performance of that and the less computationally-intensive quadratic probing case.
2. The relation between the increase in input size and the increase in build time is: (1) slightly greater than linear for quadratic probing, (2) clearly greater than linear for double-hashing. The reasoning for this discrepancy relates back to the reasons that explain pattern 1. The additional complexity of the collision resolution function for quadratic probing gets compounded on increased input size, and there are likely more collisions occurring in the double-hashing case due to a possibly non-optimal R-value.

### Question 2 - Analysis of Searching
When observing the success of the search operations between the two different table types, it can be concluded that there are no statistically significant differences between the two. The find success rate appears very similar between both the quadratic probing and double-hashing over repeated runs of the program. Furthermore, it is evident that there exists no correlation between find success rate and input size on either of the tables. In other words, both randomly outperform eachother on different input sizes over many repeated attempts.

### Question 3 - Theoretical vs Observed Worst-Case Complexity


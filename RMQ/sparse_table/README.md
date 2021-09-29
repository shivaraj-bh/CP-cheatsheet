# RMQ using sparse table
It can be used for min/max/gcd queries<br/>
min and max query can be answered in O(1)
because overlapping ranges doesn\'t affect
the result.<br/>
But for gcd query we have to treat the length 
of the range in binary, for example 
if the length of the range is 10, the binary
will be 1010.<br/>
To answer each query we will check the highest set bit, which is 1000, so we 
check gcd of the range starting from l (starting point)
to l+8, and then we set our current l to l+8.
Then we consider the next set bit, which is 
10, hence we jump 2 steps from l to l+2 and find
gcd of previous range of length 8 with current
range of length 2, giving us the gcd of 
range of length 10 from l. <br/>
The downside being query costs O(logn)
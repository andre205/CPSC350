Tyler Andrews
2263083
Assignment 1

I referenced http://www.cplusplus.com/doc/tutorial/files/ for help with file input/output
I found out how to do toupper() on stackoverflow
Also referenced cplusplus.com for some help with rand()
For some cases of small input string lengths, the formula would generate negative numbers for 
	the length of the new string so I just made all negative numbers 0 instead. This throws off 
	the stats of the 1000 strings a little bit, but not too much. (Line 210)
NOTE: the output file ALWAYS appends so if you run the application more than once it will still 
	append to the same file

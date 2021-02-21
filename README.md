# intal

<h2>Problem Statement</h2>

Develop a C library for the integers of arbitrary length (intal).

<h4>intal</h4>
An intal is a nonnegative integer of arbitrary length, but it is sufficient for your implementation to support up to 1000 decimal digits. The integer is stored as a null-terminated string of ASCII characters. An intal is represented as a string of decimal digits ('0' thru '9') that are stored in the big-endian style. That is, the most significant digit is at the head of the string. An integer 25, for example, is stored in a string s as '2' at s[0], '5' at s[1], and null char at s[2].

<h4>Files</h4>
<ol>
<li>PES1201701122.c is the implementation file, which has the definition of all the functions declared in the header file intal.h.</li> 
<li>You can use the intal_sampletest.c for the sanity check. </li>
<li>Compile intal_sampletest.c with PES1201701122.c to sanity-check your implementation.</li>
</ol>

<h4>Commands</h4>

<code>prompt> ls </code><br>
<code>op> intal.h		intal_sampletest.c 	PES1201701122.c </code>

<code>prompt> gcc -Wall PES1201701122.c intal_sampletest.c -o mytest.out</code>

<code>prompt> ./mytest.out</code>

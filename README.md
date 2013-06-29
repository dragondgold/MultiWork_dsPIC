<h2>
</a>About</h2>
It is the firware of dsPIC microcontroller which is used by <a href="https://github.com/dragondgold/MultiWork">MultiWork Project</a>.

<h2>
</a>Build Instructions</h2>
To build for dsPIC33FJ128GP802 Mplab X project must be configured to use this dsPIC and the following defines in <code>definitions.h</code> must be set:

<li><code>#define DEBUG_ISIS          FALSE</code>

<li><code>#define TEST_BT               FALSE</code>

The first define is used when using ISIS Proteus because dsPIC33FJ128GP802 is not in Proteus libraries. The second one is used also to test sending characters instead of raw data to select different options through the UART port. 
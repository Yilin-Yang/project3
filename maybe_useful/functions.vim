"###############################################################################
" EFFECTS:  Given the function headers for Boost test cases, add curly braces,
"           a print statement giving the name of the test, and a
"           BOOST_CHECK_MESSAGE call before the end of the function.
"
" USAGE: 	Put the contents of this file in your .vimrc, or put it in a file
" 			that gets `source`d in your .vimrc.
"
" 			Write a series of function headers, then
" 			`call TestCaseAutoFormat()` (or `call Tca()).
"
" 			Example:
"
"				// ElementarySchoolMathTest.cpp
"				// ...
"
"				// NOTE: no semicolons after function prototypes.
"				BOOST_AUTO_TEST_CASE(testAddingTwoAndTwo)
"				BOOST_AUTO_TEST_CASE(testSubtractingTwoAndTwo)
"				BOOST_AUTO_TEST_CASE(testMultiplyingTwoAndTwo)
"
"			:call Tca()
"
"				// ElementarySchoolMathTest.cpp,
"				//		after function call
"				// ...
"
"				BOOST_AUTO_TEST_CASE(testAddingTwoAndTwo)
"				{
"					BOOST_TEST_MESSAGE(testAddingTwoAndTwo);
"
"					BOOST_CHECK_MESSAGE(, "testAddingTwoAndTwo failed!);
"				}
"
"				BOOST_AUTO_TEST_CASE(testSubtractingTwoAndTwo)
"				{
"					BOOST_TEST_MESSAGE(testSubtractingTwoAndTwo);
"
"					BOOST_CHECK_MESSAGE(, "testAddingTwoAndTwo failed!);
"				}
"
"				BOOST_AUTO_TEST_CASE(testMultiplyingTwoAndTwo)
"				{
"					BOOST_TEST_MESSAGE(testMultiplyingTwoAndTwo);
"
"					BOOST_CHECK_MESSAGE(, "testMultiplyingTwoAndTwo failed!);
"				}
"
"###############################################################################

function TestCaseAutoformat()
	" %								=	on all lines,
	" s/{search}/{replace}/flags	= 	substitution command
	" s:{search}:{replace}:flags	=	substitution command, using
	" 										full-colon as a divider instead of
	" 										the standard forward slash
	" 									(useful if the search or replace
	" 										pattern contains the `/`
	" 										character; you won't have to
	" 										escape the `/` with a backslash
	" 										this way)
	" Within the search pattern,
	"	\( ... \)					= 	'remember' what's between the
	"									parentheses
	"									the `\` is an escape character; in
	"									 	this case, it tells vim that the `(`
	"									 	is a `special` `(`.
	"									A `(` or `)` by itself, without a
	"									backslash, is treated as a normal
	"									set of parentheses.
	"	.*							= 	in a regular expression,
	"									the `.` (period) matches one of any
	"										character
	"									the `*` (asterisk) matches any
	"										number (i.e. [0, +inf) ) of the
	"										preceding character
	"									`.*` matches `anything`
	"
	" Within the replacement,
	" 	\1							=	insert the first `remembered` set of
	" 									characters
	" 	\r							=	`press the enter key`
	" 									(NOTE: when you're trying to match a
	" 									newline character, search for \n, not
	" 									\r)
	" 	\t							=	a tab character
    %s/BOOST_AUTO_TEST_CASE(\(.*\))/BOOST_AUTO_TEST_CASE(\1)\r{\r\tBOOST_TEST_MESSAGE("\1");\r\t\r\tBOOST_CHECK_MESSAGE(,"\1 failed!");\r}\r

	" Short for `:nohighlight`, which stops highlighting things.
	" In neovim, performing a search or a search-and-replace highlights every
	" 	piece of text that could get matched by the search pattern.
    noh
endfunction

"###############################################################################
" EFFECTS:  Calls TestCaseAutoFormat().
"###############################################################################
function Tca()
    call TestCaseAutoformat()
endfunction

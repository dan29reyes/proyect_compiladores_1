%%
[0-9]+		{ return Token::NUMBER }
[a-zA-Z]+ 	{ return Token::IDENTIFIER }
[ \t]		{ /* IGNORAR */ }
<<EOF>>		{ return Token::END_OF_FILE }
%%

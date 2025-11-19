%%
'-'?[0-9]+		    { return Token::NUMBER }
[a-zA-Z_]+      	{ return Token::IDENTIFIER }
[ \t\r\n/]*		    { /* IGNORAR */ }
'/'                 { return Token::DIV_OPERATOR }
'+'                 { return Token::ADD_OPERATOR }
'*'                 { return Token::MULT_OPERATOR }
'-'                 { return Token::SUB_OPERATOR }
'/''/'[.]*          { /* IGNORAR */ }
';'                 { return Token::SEMICOLON }
','                 { return Token::COMMA }
'('                 { return Token::LEFT_PAREN }
')'                 { return Token::RIGHT_PAREN }
'{'                 { return Token::LEFT_BRACE }
'}'                 { return Token::RIGHT_BRACE }
<<EOF>>		        { return Token::END_OF_FILE }
%%

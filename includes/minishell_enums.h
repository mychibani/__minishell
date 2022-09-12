#ifndef ENUM_H
# define ENUM_H

typedef enum e_type
{
	OPERATOR,
	PIPE,
	WORD,
	REDIRECTION,
	HERE_DOC,
	INVALID

} e_type;

typedef enum e_state
{
	S_QUOTED,
	D_QUOTED,
	BACKSLASH,
	UNQUOTED

} t_state;

#endif
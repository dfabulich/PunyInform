! Part of PunyInform, a standard library for writing interactive fiction using Inform 6.

Constant Grammar__Version = 2;
Constant INDIV_PROP_START 64;
Constant NULL         = $ffff;

!Constant WORDSIZE 2; ! set by the compiler from Inform 6.30

Constant ALL_WORD     = 'all';
Constant AND_WORD     = 'and';
Constant THEN_WORD    = 'then';
Constant comma_word   = 'comma,';  ! An "untypeable word" used to substitute
                                   ! for commas in parse buffers

Attribute light;
Attribute supporter;
Attribute container;
Attribute enterable;
Attribute transparent;
Attribute open;
Attribute openable;
Attribute concealed;
Attribute moved;
Attribute visited alias moved;
Attribute proper;
Attribute scenery;
Attribute static;
Attribute animate;
Attribute worn;
Attribute pluralname;
Attribute female;
Attribute neuter;

! when you order a NPC, but the command isn't understood
! See: http://www.inform-fiction.org/manual/html/s18.html
Fake_Action Order; 
Fake_Action ThrownAt;
Fake_Action NotUnderstood; 

! Property name; ! This seems to be hardcoded in the Inform compiler
Property initial;
Property description;
Property short_name;
Property add_to_scope;
Property react_after;
Property react_before;
Property after;
Property before;
Property parse_name;
Property capacity;

! Daemons and timers

Property additive time_out NULL;
Property daemon alias time_out;
Property time_left;

! directions
Property n_to;
Property s_to;
Property e_to;
Property w_to;
#IfDef FULL_DIRECTIONS;
Property ne_to;
Property nw_to;
Property se_to;
Property sw_to;
#EndIf;
Property u_to;
Property d_to;
Property in_to;
Property out_to;

Property cant_go;

#IfDef FULL_DIRECTIONS;
Array abbr_directions_array table 'n//' 's//' 'e//' 'w//' 'ne' 'nw' 'se' 'sw' 'u//' 'd//' ',,' ',,';
Array full_directions_array table 'north' 'south' 'east' 'west' 'northeast' 'northwest' 'southeast' 'southwest' 'up' 'down' 'in' 'out';
Array direction_properties_array table n_to s_to e_to w_to ne_to nw_to se_to sw_to u_to d_to in_to out_to;
#IfNot;
Array abbr_directions_array table 'n//' 's//' 'e//' 'w//' 'u//' 'd//' ',,' ',,';
Array full_directions_array table 'north' 'south' 'east' 'west' 'up' 'down' 'in' 'out';
Array direction_properties_array table n_to s_to e_to w_to u_to d_to in_to out_to;
#EndIf;

! Header constants
Constant HEADER_DICTIONARY   = 4;    ! 2*4 = $8
Constant HEADER_STATIC_MEM   = 7;    ! 2*7 = $c

Constant TT_OBJECT           = 1;    ! one or more words referring to an object
                                     ! it is one of NOUN_TOKEN etc. below
Constant TT_PREPOSITION      = 2;    ! e.g. 'into'
Constant TT_ROUTINE_FILTER   = 3;    ! e.g. noun=CagedCreature
Constant TT_ATTR_FILTER      = 4;    ! e.g. edible
Constant TT_SCOPE            = 5;    ! e.g. scope=Spells
Constant TT_PARSE_ROUTINE    = 6;    ! a parse routine
Constant TT_END              = 15;   ! End of grammar line

Constant NOUN_TOKEN         = 0;    ! The elementary grammar tokens, and
Constant HELD_TOKEN         = 1;    ! the numbers compiled by Inform to
Constant MULTI_TOKEN        = 2;    ! encode them
Constant MULTIHELD_TOKEN    = 3;
Constant MULTIEXCEPT_TOKEN  = 4;
Constant MULTIINSIDE_TOKEN  = 5;
Constant CREATURE_TOKEN     = 6;
Constant SPECIAL_TOKEN      = 7;
Constant NUMBER_TOKEN       = 8;
Constant TOPIC_TOKEN        = 9;

! $42 = Single prep, $62 = Beginning of list of alternatives, $72 = middle of list, $52 = end of list
Constant TOKEN_SINGLE_PREP   = $42;
Constant TOKEN_FIRST_PREP    = $62;
Constant TOKEN_MIDDLE_PREP   = $72;
Constant TOKEN_LAST_PREP     = $52;

Constant GS_PLAYING          = 1;
Constant GS_QUIT             = 2;
Constant GS_DEAD             = 3;
Constant GS_WIN              = 4;
Constant GS_DEATHMESSAGE     = 5;

Constant FORM_CDEF           = 1;
Constant FORM_DEF            = 2;
Constant FORM_INDEF          = 3;

#IfV3;
Constant DICT_BYTES_FOR_WORD = 4;
#IfNot;
Constant DICT_BYTES_FOR_WORD = 6;
Constant HDR_SCREENHCHARS    = $20;
Constant HDR_SCREENWCHARS    = $21;
Constant MOVES__TX = "Moves: ";
Constant SCORE__TX = "Score: ";
#EndIf;

Default MAX_CARRIED         100;
Default SACK_OBJECT         0;

Global location = 1; ! Must be first global
Global status_field_1 = 0; ! Must be second global. Is used to show score or hours
Global status_field_2 = 0; ! Must be third global. Is used to show turns or minutes
Global score;
Global turns;
Global player;
Global actor;
Global action;
Global meta;      ! if the verb has the meta attribute or not
Global verb_word;
Global verb_wordnum;
Global noun;
Global second;
Global inp1;
Global inp2;
Global game_state;
Global wn;
Global scope_objects;
Global reverse;
Global keep_silent;
Global consult_from;  !TODO remove? ! Word that a "consult" topic starts on
Global consult_words; !TODO remove? ! ...and number of words in topic
#IfV5;
Global statusline_current_height = 0;
Global statusline_height     = 1;
Global statuswin_current     = false;
Global clr_on                = false;
Global clr_bg                = 2;
Global clr_fg                = 8;
Global clr_bgstatus          = 2;
Global clr_fgstatus          = 8;
#endif;

#ifdef DEBUG;
Global debug_flag            = 0;
#endif;

Constant MAX_INPUT_CHARS     = 78;
Constant MAX_INPUT_WORDS     = 20;

Constant WORD_HIGHBIT = $8000;
#Ifndef MAX_TIMERS;
Constant MAX_TIMERS  32;            ! Max number timers/daemons active at once
#Endif; ! MAX_TIMERS
Array  the_timers  --> MAX_TIMERS;
Global active_timers;               ! Number of timers/daemons active
Global current_timer;               ! Index of the timer which is currently being executed

Array which_object-->10;      ! options for "which do you mean?"
Array multiple_objects-->32;  ! holds nouns when multi* grammar used

Array player_input_array->(MAX_INPUT_CHARS + 3);
Array parse_array->(2 + 4 * (MAX_INPUT_WORDS + 1)); ! + 1 to make room for an extra word which is set to 0

! extra arrays to be able to ask for additional info (do you mean X or Y?)
Array temp_player_input_array->(MAX_INPUT_CHARS + 3);
Array temp_parse_array->(2 + 4 * (MAX_INPUT_WORDS + 1)); 

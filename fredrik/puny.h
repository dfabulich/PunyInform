Attribute light;

Constant TT_PREPOSITION      = 2;    ! e.g. 'into'
Constant TT_ROUTINE_FILTER   = 3;    ! e.g. noun=CagedCreature
Constant TT_ATTR_FILTER      = 4;    ! e.g. edible
Constant TT_SCOPE            = 5;    ! e.g. scope=Spells
Constant TT_PARSE_ROUTIME    = 6;    ! a parse routine
Constant TT_END              = 15;   ! End of grammar line

Constant GS_PLAYING          = 1;
Constant GS_QUIT             = 2;
Constant GS_DEAD             = 3;

#IfV3;
Constant DICT_BYTES_FOR_WORD = 4;
#IfNot;
Constant DICT_BYTES_FOR_WORD = 6;
#EndIf;

Global location = 0; ! Must be first global
Global game_state;

Constant MAX_INPUT_CHARS     = 78;
Constant MAX_INPUT_WORDS     = 20;

Array player_input_array->(MAX_INPUT_CHARS + 3);
Array parse_array->(2 + 4 * MAX_INPUT_WORDS);

! ######################### Grammar + Actions
[QuitSub;
	game_state = GS_QUIT;
];

[TakeSub a b c;
	game_state = GS_QUIT;
];

Verb 'quit'
	* 'into' noun -> Quit
	* 'out' 'of' -> Take;

! ######################### Parser

[read_player_input   result;
	print ">";
	parse_array->0 = MAX_INPUT_WORDS;
#IfV5;
	player_input_array->0 = MAX_INPUT_CHARS;
	player_input_array->1 = 0;
	@aread player_input_array parse_array -> result;
#IfNot;
	player_input_array->0 = MAX_INPUT_CHARS - 1;
	@sread player_input_array parse_array;
#EndIf;
];

[parse_and_perform_action   verb word_data verb_num verb_grammar;
	print "Adj: ", #adjectives_table;
	if(parse_array->1 < 1) {
		"Come again?";
	}
	verb = parse_array-->1;
	if(verb < (0-->4)) {
		"That is not a verb I recognize.";
	}

	word_data = verb + DICT_BYTES_FOR_WORD;
	if((word_data->0) & 1 == 0) { ! This word does not have the verb flag set.
		"That is not a verb I recognize.";
	}

	! Now we know that the first word is a verb

	verb_num = 255 - (word_data->1);
!	print "Verb#: ",verb_num,".";
	verb_grammar = (0-->7)-->verb_num;
!	print "Grammar: ",verb_grammar," (address)";


	if(parse_array->1 == 1 && parse_array-->1 == 'quit') {
		game_state = GS_QUIT;
	} else {
		print "Sorry, I didn't understand that.^";
	}
];



[main;
	print "PunyInform 0.0^^";
	game_start();
	game_state = GS_PLAYING;
	while(game_state == GS_PLAYING) {
		read_player_input();
		parse_and_perform_action();
	}
];


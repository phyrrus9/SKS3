Version 3.0.1:
	Developer mode changes. Mods can now use the following commands:
	zombie <int location> (create a zombie)
	global <string field>
		fields:
			noblock (allow re-enabling)
	require <string field> <char op> <int value>
		fields:
			env->position (position environment variable)
		ops:
			=
			<
			>
		values: 0 <= x

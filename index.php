<!DOCTYPE html>
<html name="html">
<head>
	<title>Blog Projet</title>
	<link rel="icon" type="image/png" href="img/favicon.png" />


	<link rel="stylesheet" type="text/css" href="css/style.css">
	<link rel="stylesheet" type="text/css" href="css/code.css">

	<!-- js librairie -->
	<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
	<script type="text/javascript" src="js/script_menu.js"></script>
	<script src="https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js?skin=sunburst"></script>
</head>
<body name="body">

<div id="menu">
	<ul>
		<li><a href="#">test</a></li>
		<li><a href="#">test</a></li>
		<li><a href="#">test</a></li>
		<li><a href="#">test</a></li>
		<li><a href="#">test</a></li>
		<li><a href="#">test</a></li>
		<li><a href="#">test</a></li>
		
		<li><a href="#">test</a></li>
		<li><a href="#">test</a></li>
		<li><a href="#">test</a></li>
		<li><a href="#">test1</a></li>
	</ul>

	<div id="menu_btn">
		<img class="btn" src="img/menu.svg">
	</div>
</div>
<div class="animation">
	<div class="mario"></div>
	<div class="cloud"></div>
	<div class="mountain1" id="mountain0"></div>
	<div class="mountain2" id="mountain1"></div>
	<div class="mountain1" id="mountain2"></div>
</div>
<div class="content" id="content">
	<article>
		<h1>Hello world</h1>
		<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
		tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
		quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
		consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
		cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
		proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>
		<div class="code" >
			<pre class="prettyprint lang-cpp">
#define _CRT_SECURE_NO_DEPRECATE
#include stdio.h
#include stdlib.h
#include time.h
#include string.h

#pragma pack(push,1)

#define MAGIC_VALUE 0xBEEFFABE
typedef struct timing_file_header{
    int unsigned MagicValue;
} timing_file_header;

typedef struct timing_file_date{
    long long unsigned E;
} timing_file_date;

enum timing_file_entry_flag{
    TFEF_Complete = 0x1,
    TFEF_NoErrors = 0x2,
};
typedef struct timing_file_entry{
    timing_file_date StartDate;
    int unsigned Flags;
    int unsigned MillisecondsElapsed;
} timing_file_entry;

#pragma pack(pop)

typedef struct timing_entry_array{
    int EntryCount;
    timing_file_entry *Entries;
} timing_entry_array;

// TODO(doc): more platforms

#ifdef _WIN32

#include windows.h

static int unsigned
GetClock(void){
    if(sizeof(int unsigned) != sizeof(DWORD)){
        fprintf(stderr, "ERROR: Unexpected integer size - timing will not work on this platform!\n");
    }
    
    return(timeGetTime());
}

#else

// This was written for Linux

static int unsigned
GetClock(void){
    struct timespec TimeSpec;
    int unsigned Result;
    
    clock_gettime(CLOCK_REALTIME, &TimeSpec);
    Result = TimeSpec.tv_sec * 1000 + TimeSpec.tv_nsec / 1000000;
    
    return Result;
}


#endif

//
//
//

static timing_file_date
GetDate(void){
    timing_file_date Result = {0};
    Result.E = time(NULL);
    return(Result);
}

static void
PrintDate(timing_file_date Date){
    time_t Time;
    struct tm *LocalTime;
    char Str[256];
    
    Time = Date.E;
    LocalTime = localtime(&Time);
    strftime(Str, 256, "%Y-%m-%d %H:%M:%S", LocalTime);
    fprintf(stdout, "%s", Str);
}
			</pre>
		</div>
	</article>	
	<article>
		<h1>Hello world</h1>
		<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
		tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
		quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
		consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
		cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
		proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>
	</article>	
	<article>
		<h1>Hello world</h1>
		<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
		tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
		quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
		consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
		cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
		proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>
	</article>	
</div>


<div id="sound_btn">
	<img src="img/speaker.svg" id="svg_song" class="invisible">
	<img src="img/mute.svg" id="svg_mute">
</div>

<script type="text/javascript" src="js/script_song.js"></script>
</body>
</html>
cmake_minimum_required(VERSION 3.10)
project(cgame LANGUAGES C VERSION 0.0.0.1)

add_compile_options(-DCORE_SET_DEBUG_COLORED)

set(LOCAL_COMPLILE_OPTIONS
	-std=c99 -pedantic
	$<$<NOT:$<CONFIG:RELEASE>>:
		-Wall -Wextra
    	-Wno-missing-braces -Wno-missing-field-initializers -Wformat=2 
    	-Wswitch-default -Wswitch-enum -Wcast-align -Wpointer-arith 
    	-Wbad-function-cast -Wstrict-overflow=5 -Wstrict-prototypes -Winline 
    	-Wundef -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code 
    	-Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 -Wredundant-decls 
    	-Wold-style-definition
    	-ggdb3 
    	-O0 
    	-fno-omit-frame-pointer -ffloat-store -fno-common -fstrict-aliasing 
    >
    $<$<CONFIG:RELEASE>:
    	-O3
     	-funroll-loops
    	-DNDEBUG
    >
)

add_executable(cgame 
	main.c
	window.c
	player.c
	enemies.c
	projectile.c
	direction.c
	log.c
)
target_link_libraries(cgame PUBLIC 
	CCORE
	ncurses
)
target_compile_options(cgame PRIVATE ${LOCAL_COMPLILE_OPTIONS})

add_subdirectory(libCCORE)

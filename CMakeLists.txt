CMAKE_MINIMUM_REQUIRED( VERSION 3.0 )

PROJECT( term )

ADD_EXECUTABLE(term
        main.c
        process.c
        queue.c
        dllist.c
        )
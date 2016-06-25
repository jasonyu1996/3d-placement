HEADERS += \
    kernel.h \
    ContourStructure/contourstructure.h \
    ContourStructure/segmentree.h \
    Strategy/ttree.h \
    Strategy/boxpackagevaluestrategy.h \
    Strategy/boxvolume.h \
    boxpacker.h \
    saoptimalboxpacker.h \
    Strategy/boxperturber.h \
    ContourStructure/naivecontourstructure.h \
    ContourStructure/contourstructurefactory.h \
    Strategy/boxperturberfactory.h \
    Strategy/ttreefactory.h \
    ContourStructure/naivecontourstructurefactory.h \
    ContourStructure/kdtreecontourstructure.h \
    ContourStructure/kdtreecontourstructurefactory.h

SOURCES += \
    main.cpp \
    Strategy/ttree.cpp \
    kernel.cpp \
    ContourStructure/naivecontourstructure.cpp \
    ContourStructure/kdtreecontourstructure.cpp \
    saoptimalboxpacker.cpp

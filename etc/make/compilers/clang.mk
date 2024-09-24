.EXPORT_ALL_VARIABLES:

CXXFLAGS	+=	-fshow-source-location
CXXFLAGS	+=	-fshow-column
CXXFLAGS	+=	-fdelete-null-pointer-checks
CXXFLAGS	+=	-fsized-deallocation
CXXFLAGS	+=	-fstack-protector
CXXFLAGS	+=	-fstrict-enums

LDFLAGS		+=	-Wl,--demangle

WARNS	+=	-Weverything
WARNS	+=	-Wno-padded
WARNS	+=	-Wno-c99-extensions
WARNS	+=	-Wno-c99-compat
WARNS	+=	-Wno-c++-compat
WARNS	+=	-Wno-c++20-compat
WARNS	+=	-Wno-c++98-compat
WARNS	+=	-Wno-c++98-compat-pedantic
WARNS	+=	-Wno-pre-c++20-compat-pedantic
WARNS	+=	-Wno-pre-c++17-compat-pedantic
WARNS	+=	-Wno-switch-default

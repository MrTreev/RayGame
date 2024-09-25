clang_warnings = [
    "-Weverything",
    "-pedantic",
    "-Wno-padded",
    "-Wno-c99-extensions",
    "-Wno-c99-compat",
    "-Wno-c++-compat",
    "-Wno-c++20-compat",
    "-Wno-c++98-compat",
    "-Wno-c++98-compat-pedantic",
    "-Wno-pre-c++20-compat-pedantic",
    "-Wno-pre-c++17-compat-pedantic",
    "-Wno-switch-default",
]

gcc_warnings = [
    "-Wall",
    "-Wextra",
    "-Wshadow",
    "-Wnon-virtual-dtor",
    "-Wold-style-cast",
    "-Wcast-align",
    "-Wunused",
    "-Woverloaded-virtual",
    "-Wpedantic",
    "-Wconversion",
    "-Wsign-conversion",
    "-Wnull-dereference",
    "-Wdouble-promotion",
    "-Wformat=2",
    "-Wimplicit-fallthrough",
    "-Wmisleading-indentation",
    "-Wduplicated-cond",
    "-Wduplicated-branches",
    "-Wlogical-op",
    "-Wuseless-cast",
    "-Wsuggest-override",
]

msvc_warnings = [
    "/W4",
    "/w14242",
    "/w14254",
    "/w14263",
    "/w14265",
    "/w14287",
    "/we4289",
    "/w14296",
    "/w14311",
    "/w14545",
    "/w14546",
    "/w14547",
    "/w14549",
    "/w14555",
    "/w14619",
    "/w14640",
    "/w14826",
    "/w14905",
    "/w14906",
    "/w14928",
    "/permissive-",
]

clang_analysis = [
    "-fverify-intermediate-code",
]

opt_args = [
    "-Ofast",
    "-DNDEBUG",
    "-ffast-math",
    "-flto=full",
    "-fshort-enums",
    "-funroll-loops",
    "-fvectorize",
    "-fvirtual-function-elimination",
    "-fwhole-program-vtables",
]

safety_args = [
    "-fstack-protector-all",
]

main_args = [
    "-fstrict-enums",
]

debug_info = [
    "-DDEBUG"
    "-g"
    "-gfull"
    "-gsplit-dwarf"
    "-ggdb"
]

def conlyopts(buildtype, arch, cpu, compiler, version):
    conlyopts = []
    return conlyopts

def copts(buildtype, arch, cpu, compiler, version):
    copts = []
    if buildtype == "release":
        copts.extend(
            opt_args
        )
    if buildtype == "opt":
        copts.extend(
            opt_args
        )
    if buildtype == "fast":
        copts.extend(
        )
    if buildtype == "dbg":
        copts.extend(
            [
                "-fno-unroll-loops"
                "-fno-omit-frame-pointer"
                "-fno-inline"
                "-funwind-tables"
            ] +
            safety_args +
            debug_info
        )
    return copts

def cxxopts(buildtype, arch, cpu, compiler, version):
    cxxopts = ["-Werror"] if buildtype != "msvc" else []
    if compiler == "clang":
        cxxopts.extend(clang_warnings)
    if compiler == "gcc":
        cxxopts.extend(gcc_warnings)
    if compiler == "msvc":
        cxxopts.extend(msvc_warnings)
    return cxxopts

def linkopts(buildtype, arch, cpu, compiler, version):
    linkopts = []
    return linkopts

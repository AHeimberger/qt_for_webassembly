TARGET = dev-setup

CONFIG += \
    c++11 \
    warn_on \
    # hide_all

# Turn on warnings, except for code that is Qt-generated
WARNINGS += -Wextra
WARNINGS += -Wunknown-pragmas -Wundef
WARNINGS += -Wold-style-cast
WARNINGS += -Wdisabled-optimization -Wstrict-overflow=4
# WARNINGS += -Weffc++ -Wuseless-cast
WARNINGS += -Winit-self -Wpointer-arith
WARNINGS += -Wlogical-op
WARNINGS += -Wunsafe-loop-optimizations -Wno-error=unsafe-loop-optimizations
QMAKE_CXXFLAGS_WARN_ON += $(and $(filter-out moc_% qrc_%, $@),$${WARNINGS})

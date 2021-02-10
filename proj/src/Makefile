PROG=proj

SRCS = proj.c graphic.c keyboard.c timer.c utils.c sprite.c while_game.c mouse.c file.c rtc.c user.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>

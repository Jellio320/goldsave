OUTPUT = goldsave

srcdir = src
objdir = obj
depdir = $(objdir)/.deps

CC = gcc
DEPFLAGS = -MT $@ -MMD -MP -MF $(depdir)/$*.d
CPPFLAGS = $(DEPFLAGS)
CFLAGS = -std=c99 -Wall -Wextra -O2 -g0
LD = $(CC)

SRCS := $(wildcard $(srcdir)/*.c)
OBJS := $(patsubst $(srcdir)/%.c, $(objdir)/%.o, $(SRCS))
DEPS := $(patsubst $(srcdir)/%.c, $(depdir)/%.d, $(SRCS))

.PHONY: clean

$(OUTPUT): $(OBJS)
	$(LD) $^ -o $@

clean:
	$(RM) $(OUTPUT) $(objdir)/*.o


$(objdir)/%.o: $(srcdir)/%.c $(depdir)/%.d | $(depdir)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(DEPS):
include $(wildcard $(DEPS))

$(depdir):
	@mkdir -p $@
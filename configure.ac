AC_PREREQ(2.54)

dnl ===========================================================================

m4_define(glib_minver,                 2.36.0)
m4_define(gio_minver,                  2.26.0)
m4_define(ukui_desktop_minver,         1.15.1)
m4_define(pango_minver,                1.1.2)
m4_define(gtk_minver,                  2.24.0)
m4_define(xml_minver,                  2.4.7)
m4_define(exif_minver,                 0.6.14)
m4_define(exempi_minver,               1.99.5)
m4_define(gail_minver,                 0.16)


dnl 1. If the library code has changed at all since last release, then increment revision.
dnl 2. If any interfaces have been added, then increment current and set revision to 0.
dnl Interface break is not allowed.
m4_define(peony_extension_current,  5)
m4_define(peony_extension_revision, 0)

AC_INIT([peony], [1.16.0], [http://www.ukui.org])

dnl ---------------------------------------------------------------------------
dnl GTK library version
dnl ---------------------------------------------------------------------------
AC_MSG_CHECKING([which gtk+ version to compile against])
AC_ARG_WITH([gtk],
    [AS_HELP_STRING([--with-gtk=2.0|3.0],[which gtk+ version to compile against (default: 2.0)])],
    [
        case "$with_gtk" in
            2.0|3.0) ;;
            *) AC_MSG_ERROR([invalid gtk version specified]) ;;
        esac
    ],
    [with_gtk=2.0])
AC_MSG_RESULT([$with_gtk])

case "$with_gtk" in
  2.0) GTK_API_VERSION=2.0
       GTK_REQUIRED=2.24.0
       GAIL_API_VERSION=
       LIBUNIQUE_VERSION=1.0
       ;;
  3.0) GTK_API_VERSION=3.0
       GTK_REQUIRED=3.0.0
       GAIL_API_VERSION=-3.0
       LIBUNIQUE_VERSION=3.0
       ;;
esac
AC_SUBST([GTK_API_VERSION])

dnl ===========================================================================

AC_CONFIG_SRCDIR(src)
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.9 tar-ustar dist-xz no-dist-gzip check-news])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_MAINTAINER_MODE
AC_SUBST([ACLOCAL_AMFLAGS], ["\${ACLOCAL_FLAGS}"])

AC_SUBST(GLIB_REQUIRED, [glib_minver])
AC_SUBST(GIO_REQUIRED, [gio_minver])
AC_SUBST(UKUI_DESKTOP_REQUIRED, [ukui_desktop_minver])
AC_SUBST(PANGO_REQUIRED, [pango_minver])
AC_SUBST(GTK_REQUIRED, [$GTK_REQUIRED])
AC_SUBST(XML_REQUIRED, [xml_minver])
AC_SUBST(GAIL_REQUIRED)

dnl We need to decrement current by one in the calculation of the age because
dnl the library was started with version "1:0:0" instead of "0:0:0"
AC_SUBST(PEONY_EXTENSION_VERSION_INFO, [peony_extension_current]:[peony_extension_revision]:`expr [peony_extension_current] - 1`)

AC_C_BIGENDIAN
AC_C_CONST
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_DISABLE_STATIC
AM_PROG_LIBTOOL
AC_PATH_PROG(PKG_CONFIG, pkg-config, no)

AC_CHECK_LIB(m, floor)

PKG_CHECK_MODULES(ALL, [
    glib-2.0 >= glib_minver
    ukui-desktop-2.0 >= ukui_desktop_minver
    gthread-2.0
    gio-unix-2.0
    gio-2.0 >= gio_minver
    pango >= pango_minver
    gtk+-$GTK_API_VERSION >= $GTK_REQUIRED
    libxml-2.0 >= xml_minver
    gail$GAIL_API_VERSION >= gail_minver
])
dnl ==========================================================================

GETTEXT_PACKAGE=peony
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE",
    [the gettext translation domain])

AH_TEMPLATE([ENABLE_INSTALLER])
AH_TEMPLATE([ENABLE_NLS])
AH_TEMPLATE([GETTEXT_PACKAGE])
AH_TEMPLATE([HAVE_CATGETS])
AH_TEMPLATE([HAVE_GETTEXT])
AH_TEMPLATE([HAVE_LC_MESSAGES])
AH_TEMPLATE([HAVE_LIBBZ2])
AH_TEMPLATE([HAVE_LIBJPEG])
AH_TEMPLATE([HAVE_MEDUSA])
AH_TEMPLATE([HAVE_STPCPY])
AH_TEMPLATE([bzclose])
AH_TEMPLATE([bzCompress])
AH_TEMPLATE([bzCompressInit])
AH_TEMPLATE([bzDecompress])
AH_TEMPLATE([bzDecompressInit])
AH_TEMPLATE([bzdopen])
AH_TEMPLATE([bzerror])
AH_TEMPLATE([bzflush])
AH_TEMPLATE([bzopen])
AH_TEMPLATE([bzread])
AH_TEMPLATE([bzwrite])

AC_DEFINE([HAVE_GTK_MULTIHEAD], [], [needed for egg-screen-exec functions])

AH_TEMPLATE([HAVE_STARTUP_NOTIFICATION])
AH_TEMPLATE([HAVE_EXIF])
AH_TEMPLATE([HAVE_RENDER])

AM_GLIB_GNU_GETTEXT
GLIB_DEFINE_LOCALEDIR(UKUILOCALEDIR)

IT_PROG_INTLTOOL([0.50.1])

dnl ==========================================================================

GTK_DOC_CHECK([1.4])

dnl ==========================================================================

AC_CHECK_PROGS(PERL, perl5 perl)
AC_PATH_PROG(GLIB_GENMARSHAL, glib-genmarshal)

dnl ==========================================================================

AC_CHECK_HEADERS(sys/mount.h sys/vfs.h sys/param.h malloc.h)
AC_CHECK_FUNCS(mallopt)

dnl ==========================================================================

AM_CONDITIONAL(HAVE_EXIF, false)

dnl libexif checking

PKG_CHECK_MODULES(EXIF, libexif >= exif_minver,
    [AM_CONDITIONAL(HAVE_EXIF, true)
     AC_DEFINE(HAVE_EXIF, 1, [Define to enable EXIF support])
    ],
    [AM_CONDITIONAL(HAVE_EXIF, false)])

AC_SUBST(EXIF_CFLAGS)
AC_SUBST(EXIF_LIBS)

dnl ==========================================================================

dnl exempi checking

AM_CONDITIONAL(HAVE_EXEMPI, false)

AC_ARG_ENABLE(xmp,
    AC_HELP_STRING([--disable-xmp],
                   [build without xmp support]))
msg_xmp=no
if test "x$enable_xmp" != "xno"; then
    PKG_CHECK_MODULES(EXEMPI, exempi-2.0 >= exempi_minver,
        [AM_CONDITIONAL(HAVE_EXEMPI, true)
         AC_DEFINE(HAVE_EXEMPI, 1, [Define to enable xmp support])]
        msg_xmp=yes,
        [AM_CONDITIONAL(HAVE_EXEMPI, false)])

    AC_SUBST(EXEMPI_CFLAGS)
    AC_SUBST(EXEMPI_LIBS)
fi

dnl ==========================================================================

dnl ****************************
dnl *** Check for libselinux ***
dnl ****************************

SELINUX_LIBS=
msg_selinux=no
AC_CHECK_LIB(selinux, is_selinux_enabled,
   [AC_CHECK_HEADERS(selinux/selinux.h,
     [AC_SEARCH_LIBS(selinux_raw_to_trans_context, selinux,
       [AC_DEFINE(HAVE_SELINUX, 1, [Define to 1 if libselinux is available])
        SELINUX_LIBS="-lselinux"
        msg_selinux=yes])
     ])
   ])
AC_SUBST(SELINUX_LIBS)


AC_ARG_ENABLE(empty_view,
 AC_HELP_STRING([--enable-empty-view], [Enable empty view]),
 [ENABLE_EMPTY_VIEW=1
  AC_DEFINE(ENABLE_EMPTY_VIEW, 1, [define to enable the empty view that is used for performance measurement])])

AC_SUBST(ENABLE_EMPTY_VIEW)
AM_CONDITIONAL(ENABLE_EMPTY_VIEW, test "x$ENABLE_EMPTY_VIEW" = "x1")

dnl ==========================================================================

AC_ARG_ENABLE(packagekit,
    AC_HELP_STRING([--disable-packagekit],
        [build without PackageKit support]))
msg_packagekit=no
if test "x$enable_packagekit" != "xno"; then
    msg_packagekit=yes
    AC_DEFINE(ENABLE_PACKAGEKIT, 1, [define to enable PackageKit mimetype installer])
fi


#============================================================================
# libunique
#============================================================================
PKG_CHECK_MODULES(UNIQUE, unique-$LIBUNIQUE_VERSION)

AC_SUBST([UNIQUE_CFLAGS])
AC_SUBST([UNIQUE_LIBS])

# this deprecated stuff should be removed from unique in most distros
# but it's still not removed upstream in unique 1.x, so leaving it alone
# just in case.
UNIQUE_CFLAGS="$UNIQUE_CFLAGS -DG_CONST_RETURN=const"

EXTRA_CORE_MODULES="$EXTRA_CORE_MODULES unique-$LIBUNIQUE_VERSION"


# ==========================================================================
# Turn on the additional warnings last, so -Werror doesn't affect other tests.

WARNING_CFLAGS=""

AC_ARG_ENABLE(more-warnings,
AC_HELP_STRING([--enable-more-warnings], [Maximum compiler warnings]),
set_more_warnings="$enableval",[
if test -f $srcdir/CVSVERSION; then
    is_cvs_version=true
    set_more_warnings=yes
else
    set_more_warnings=no
fi
])
AC_MSG_CHECKING(for more warnings, including -Werror)
if test "$GCC" = "yes" -a "$set_more_warnings" != "no"; then
    AC_MSG_RESULT(yes)
    WARNING_CFLAGS="\
    -Wall \
    -Wmissing-declarations -Wmissing-prototypes \
    -Wnested-externs -Wpointer-arith \
    -Wcast-align \
    -Werror"

    for option in -Wstrict-aliasing=0 -Wno-pointer-sign; do
        SAVE_CFLAGS="$CFLAGS"
        CFLAGS="$CFLAGS $option"
        AC_MSG_CHECKING([whether gcc understands $option])
        AC_TRY_COMPILE([], [],
            has_option=yes,
            has_option=no,)
        if test $has_option = yes; then
            WARNING_CFLAGS="$WARNING_CFLAGS $option"
        fi
        AC_MSG_RESULT($has_option)
        CFLAGS="$SAVE_CFLAGS"
        unset has_option
        unset SAVE_CFLAGS
    done
    unset option
else
    AC_MSG_RESULT(no)
fi

AC_SUBST(WARNING_CFLAGS)

dnl ===========================================================================

dnl strftime checks

AC_TRY_RUN([#include <time.h>
                int main ()
                {
                  char buf[100];
                  struct tm tm = {0};
                  tm.tm_year = 99;
                  if (strftime(buf, 100, "%EY", &tm) == 4 &&
                      strcmp (buf, "1999")==0)
                    return 0;
                  return 1;
                }
            ],
    AC_DEFINE(HAVE_STRFTIME_EXTENSION, 1, [Define if strftime supports %E and %O modifiers.])
)

dnl ===========================================================================

#
# Checks for Xft/XRender
#

PKG_CHECK_MODULES([RENDER], [xrender xext], [have_render=yes], [have_render=no])
if test x$have_render = xyes; then
  AC_DEFINE(HAVE_RENDER)
  AC_SUBST(RENDER_CFLAGS)
  AC_SUBST(RENDER_LIBS)
fi

dnl ==========================================================================

dnl libegg
LIBEGG_MODULES="gtk+-$GTK_API_VERSION"
LIBEGG_CFLAGS="`$PKG_CONFIG --cflags $LIBEGG_MODULES`"
AC_SUBST(LIBEGG_CFLAGS)
LIBEGG_LIBS="`$PKG_CONFIG --libs $LIBEGG_MODULES`"
AC_SUBST(LIBEGG_LIBS)

dnl libpeony-extension
LIBPEONY_EXTENSION_MODULES="glib-2.0 gtk+-$GTK_API_VERSION"
LIBPEONY_EXTENSION_CFLAGS="`$PKG_CONFIG --cflags $LIBPEONY_EXTENSION_MODULES`"
AC_SUBST(LIBPEONY_EXTENSION_CFLAGS)
LIBPEONY_EXTENSION_LIBS="`$PKG_CONFIG --libs $LIBPEONY_EXTENSION_MODULES`"
AC_SUBST(LIBPEONY_EXTENSION_LIBS)

dnl core peony
PKG_CHECK_MODULES(GMODULE, gmodule-2.0, [GMODULE_ADD="gmodule-2.0"],[GMODULE_ADD=""])
CORE_MODULES="glib-2.0 $GMODULE_ADD ukui-desktop-2.0 gthread-2.0 gio-2.0 gio-unix-2.0 gail$GAIL_API_VERSION libxml-2.0 $EXTRA_CORE_MODULES gtk+-$GTK_API_VERSION x11"
CORE_CFLAGS="`$PKG_CONFIG --cflags $CORE_MODULES`"
AC_SUBST(CORE_CFLAGS)
CORE_LIBS="`$PKG_CONFIG --libs $CORE_MODULES`"
AC_SUBST(CORE_LIBS)

DISABLE_DEPRECATED_CFLAGS="-DG_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED"
AC_SUBST(DISABLE_DEPRECATED_CFLAGS)

dnl Multimedia keys
AC_CHECK_HEADERS([X11/XF86keysym.h])

dnl ==============================================
dnl Special GSettings section
dnl ==============================================

GLIB_GSETTINGS

##################################################
# Check for introspection
##################################################
GOBJECT_INTROSPECTION_CHECK([0.6.4])

dnl ==========================================================================

AC_PATH_PROG(UPDATE_MIME_DATABASE, update-mime-database, no)

AC_ARG_ENABLE(update-mimedb,
   AC_HELP_STRING([--disable-update-mimedb],
                   [disable the update-mime-database after install [default=no]]),,
    enable_update_mimedb=yes)
AM_CONDITIONAL(ENABLE_UPDATE_MIMEDB, test x$enable_update_mimedb = xyes)

AC_ARG_ENABLE(icon-update, AC_HELP_STRING([--disable-icon-update],
                                        [Disable icon cache update]))
if (test "$enable_icon_update" != no); then
        AC_PATH_PROG(UPDATE_ICON_CACHE, [gtk-update-icon-cache])
fi
AM_CONDITIONAL([ICON_UPDATE], [test -n "$UPDATE_ICON_CACHE"])

AC_CONFIG_FILES([
Makefile
cut-n-paste-code/Makefile
cut-n-paste-code/libegg/Makefile
data/Makefile
data/icons/Makefile
data/patterns/Makefile
data/peony-computer.desktop.in
data/peony-file-management-properties.desktop.in
data/peony-home.desktop.in
data/peony.desktop.in
data/peony-folder-handler.desktop.in
data/peony-browser.desktop.in
data/peony-autorun-software.desktop.in
docs/Makefile
docs/reference/Makefile
docs/reference/libpeony-extension/Makefile
docs/reference/libpeony-extension/version.xml
eel/Makefile
icons/Makefile
libpeony-private/Makefile
libpeony-extension/Makefile
libpeony-extension/libpeony-extension.pc
libpeony-extension/libpeony-extension-uninstalled.pc
po/Makefile.in
src/Makefile
src/file-manager/Makefile
test/Makefile
])

AC_OUTPUT

dnl ==========================================================================

echo "
peony-$VERSION:

    prefix:                       ${prefix}
    source code location:         ${srcdir}
    compiler:                     ${CC}
    xmp support:                  $msg_xmp
    Gtk+ version:                 ${GTK_API_VERSION}
    PackageKit support:           $msg_packagekit

    peony-extension documentation: ${enable_gtk_doc}
    peony-extension introspection: ${found_introspection}
"
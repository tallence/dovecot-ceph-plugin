#
# spec file for package dovecot22-rados-plugins
#
# Copyright (c) 2017-2018 Tallence AG and the authors
#
# This is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License version 2.1, as published by the Free Software
# Foundation.  See file COPYING.

%{!?dovecot_devel: %define dovecot_devel tallence-dovecot-devel}
%{!?librados_version: %define librados_version 12.2.12}

Name:		dovecot-ceph-plugin
Summary:	Dovecot Ceph RADOS plugins

Version:	1.0.1

Release:	0%{?dist}
URL:		https://github.com/ceph-dovecot/dovecot-ceph-plugin
Group:		Productivity/Networking/Email/Servers
License:	LGPL-2.1
Source:		%{name}_%{version}-%{release}.tar.gz

Provides:	dovecot-ceph-plugin = %{version}-%{release}
Requires:	librmb0 >= %{version}-%{release}
Conflicts:	otherproviders(dovecot-ceph-plugin)

BuildRoot:	%{_tmppath}/%{name}-%{version}-build
BuildRequires:	%dovecot_devel
BuildRequires:	librados-devel >= %librados_version
BuildRequires:	libjansson-devel >= 2.9
BuildRequires:	gcc-c++
BuildRequires:	libtool
BuildRequires:	pkg-config

%if 0%{?sle_version} > 150000
BuildRequires:	libradospp-devel >= %librados_version
%endif

%description
Dovecot is an IMAP and POP3 server for Linux and UNIX-like systems,
written primarily with security in mind. Although it is written in C,
it uses several coding techniques to avoid most of the common pitfalls.

Dovecot can work with standard mbox and maildir formats and is fully
compatible with UW-IMAP and Courier IMAP servers as well as mail
clients accessing the mailboxes directly.

This package holds the files needed for RADOS support.

%package -n librmb0
Summary:	RADOS mailbox library
Group:		System/Libraries
%description -n librmb0
Library with generic abstraction to store emails in RADOS

%package -n librmb-devel
Summary:	RADOS mailbox headers
Requires: 	librmb0 >= %{version}-%{release}
Group:		Development/Libraries/C and C++
%description -n librmb-devel
This package contains libraries and headers needed to develop programs
that use rados mailbox library.

%package -n rmb-tools
Summary:	RADOS mailbox tools
Requires: 	librmb0 >= %{version}-%{release}
Group:		Productivity/Networking/Email/Servers
%description -n rmb-tools
This package contains useful tools to manage RADOS mailbox setups.

%prep
%setup -q

%build
export CFLAGS="%{optflags}"
export CFLAGS="$CFLAGS -fpic -DPIC"
export LIBS="-pie"

./autogen.sh
%configure \
	--prefix=%{_prefix} \
	--with-dovecot=%{_libdir}/dovecot

%{__make}

%install
%makeinstall

# clean up unused files
find %{buildroot}%{_libdir}/ -type f -name \*.la -delete
find %{buildroot}%{_libdir}/dovecot/ -type f -name \*.a  -delete

%clean
%{__rm} -rf %{buildroot}

%post
/sbin/ldconfig
%postun
/sbin/ldconfig

%files
%defattr(-,root,root)
%dir %{_libdir}/dovecot
%{_libdir}/dovecot/lib*.so*
%dir %{_libdir}/dovecot/doveadm
%{_libdir}/dovecot/doveadm/lib10_doveadm_rbox_plugin.so

%files -n librmb0
%defattr(-,root,root)
%{_libdir}/librmb.so.*

%post -n librmb0 -p /sbin/ldconfig

%postun -n librmb0 -p /sbin/ldconfig

%files -n librmb-devel
%defattr(-,root,root)
%{_includedir}/*
%{_libdir}/librmb.so

%files -n rmb-tools
%defattr(-,root,root)
%attr(0755, root, root) %{_bindir}/rmb
%changelog


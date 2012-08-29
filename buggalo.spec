Summary: A simple command-line utility for extracting phylogenetic trees from files.
Name: buggalo
Version: 0.0.1
Release: 2
Epoch: 0
Group: Applications/System
BuildRoot: %{_tmppath}/%{name}/%{version}-buildroot
License: BSD
Provides: buggalo
BuildRequires: gcc-c++
BuildRequires: gcc
Requires: boost >= 1.33.1-15
Requires: iplant-ncl >= 2.1.18-1

Source0: buggalo-0.0.1.tar.gz

%description
A simple command-line utility for extracting phylogenetic trees from files.

%prep
%setup -q

%build
PREFIX=$RPM_BUILD_ROOT/usr/local make install

%clean
rm -rf $RPM_BUILD_ROOT

%files
/usr/local/bin/buggalo

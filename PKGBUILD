# Maintainer: Evgeniy Filimonov <evgfilim1@yandex.ru>

_name=pam_stackpass
pkgname=lib$_name
pkgver=0.1.0
pkgrel=1
pkgdesc='A simple C library to get or put passwords from/to PAM stack.'
# https://wiki.archlinux.org/title/PKGBUILD#arch
arch=('x86_64' 'i686' 'pentium4' 'arm' 'armv6h' 'armv7h' 'aarch64')
url="https://github.com/evgfilim1/$_name"
depends=('pam')
makedepends=('cmake')
source=("$url/archive/refs/tags/$pkgver.tar.gz")
md5sums=('3f23ba5062827e130c24d83eba451ba0')

build() {
  cd "$srcdir/$_name-$pkgver"
  rm -rf build
  mkdir build && cd build
  cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
  make
}

package() {
  cd "$srcdir/$_name-$pkgver/build"
  make DESTDIR="$pkgdir" install
}

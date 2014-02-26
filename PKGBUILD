# Maintainer: David McMackins <mcmackinsd@gmail.com>
pkgname=calccmd
pkgver=0.2.1
pkgrel=1
epoch=
pkgdesc="A free command line calculator"
arch=(any)
url="https://github.com/2mac/calcCMD/"
license=('GPL3')
groups=()
depends=()
makedepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=($pgkname-$pkgver.tar.gz)
noextract=()
md5sums=()

build() {
    cd $pkgname-$pkgver

    make
}

package() {
    cd $pkgname-$pkgver

    make DESTDIR="$pkgdir/" install
}

#include "atomic_cell.h"
#include <assert.h>
#include <escher/palette.h>

namespace Atomic {

AtomicCell::AtomicCell() :
  HighlightCell(),
  m_visible(true)
{
}

KDColor AtomicCell::colorForType(AtomType type) const {
  return Palette::AtomColor[type];
}

void AtomicCell::drawRect(KDContext * ctx, KDRect rect) const {
  if (m_visible) {
    KDColor color = colorForType(m_atom.type);
    ctx->fillRect(rect, color);

    // Get text size in pixels
    KDSize textSize = KDFont::SmallFont->stringSize(m_atom.symbol);

    // Center text in cell
    KDPoint textPosition(bounds().topLeft().x() + (bounds().width() - textSize.width()) / 2, bounds().topLeft().y() + (bounds().height() - textSize.height()) / 2);
    ctx->drawString(m_atom.symbol, textPosition, KDFont::SmallFont, Palette::PrimaryText, color);
    if (isHighlighted()) {
      KDColor highlightColor = KDColor::blend(color, Palette::AtomHighlight, 0x7F);
      ctx->strokeRect(bounds(), highlightColor);
    }
  } else {
    ctx->fillRect(rect, Palette::BackgroundApps);
  }
}

int AtomicCell::numberOfSubviews() const {
  return 0;
}

View * AtomicCell::subviewAtIndex(int index) {
  return nullptr;
}

void AtomicCell::layoutSubviews(bool force) {
}

void AtomicCell::setVisible(bool visible) {
  if (m_visible != visible) {
    m_visible = visible;
    markRectAsDirty(bounds());
  }
}

void AtomicCell::setAtom(AtomDef atom) {
  m_atom = atom;
  markRectAsDirty(bounds());
}

void AtomicCell::reloadCell() {
  markRectAsDirty(bounds());
}

}

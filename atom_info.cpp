#include "atom_info.h"
#include "kandinsky/color.h"
#include "kandinsky/rect.h"
#include <poincare/integer.h>
#include <poincare/number.h>
#include <escher/palette.h>
#include <algorithm>

namespace Atomic {

atomInfo::atomInfo() :
  View(),
  m_atomName(KDFont::SmallFont, (I18n::Message)0, 0.0f, 0.0f, Palette::PrimaryText, Palette::BackgroundApps)
{
}

void atomInfo::drawRect(KDContext * ctx, KDRect rect) const {
  // Clear the background
  ctx->fillRect(rect, Palette::BackgroundApps);

  // Get the color of the atom
  KDColor color = Palette::AtomColor[m_atom.type];

  // Get the border color
  KDColor border = KDColor::blend(color, Palette::AtomHighlight, 0x7F);

  // Draw the background
  ctx->fillRect(KDRect(rect.left() + 1, rect.top() + 1, 48, 48), color);

  // Draw the border
  ctx->strokeRect(KDRect(rect.left(), rect.top(), 50, 50), border);


  // Get the number of nucleons and protons
  char nucleons[4];
  Poincare::Integer(m_atom.num + m_atom.neutrons).serialize(nucleons, 4);

  char protons[4];
  Poincare::Integer(m_atom.num).serialize(protons, 4);

  // Get the size of the nucleons, protons and symbol strings
  KDSize nucleonsSize = KDFont::SmallFont->stringSize(nucleons);
  KDSize protonsSize = KDFont::SmallFont->stringSize(protons);
  KDSize symbolSize = KDFont::LargeFont->stringSize(m_atom.symbol);


  // Compute the position of the nucleons, protons and symbol strings to center them
  // Get the total width of the strings
  int totalWidth = std::max(nucleonsSize.width(), protonsSize.width()) + symbolSize.width();

  // Get the positions
  int nucleonsPosition = (50 - totalWidth + std::max(nucleonsSize.width(), protonsSize.width()) - nucleonsSize.width()) / 2;
  int protonsPosition = (50 - totalWidth + std::max(nucleonsSize.width(), protonsSize.width()) - protonsSize.width()) / 2;
  int symbolPosition = std::max(nucleonsPosition + nucleonsSize.width(), protonsPosition + protonsSize.width());

  // Get the y position of the nucleons and protons, and the symbol
  int nucleonsY = (50 - nucleonsSize.height() - protonsSize.height()) / 2;
  int protonsY = nucleonsY + nucleonsSize.height();
  int symbolY = (50 - symbolSize.height()) / 2;


  // Draw the number of nucleons
  KDPoint coordonates(nucleonsPosition, nucleonsY);
  ctx->drawString(nucleons, coordonates, KDFont::SmallFont, Palette::AtomText, color);

  // Draw the number of protons
  coordonates = KDPoint(protonsPosition, protonsY);
  ctx->drawString(protons, coordonates, KDFont::SmallFont, Palette::AtomText, color);

  // Draw the symbol of the atom
  coordonates = KDPoint(symbolPosition, symbolY);
  ctx->drawString(m_atom.symbol, coordonates, KDFont::LargeFont, Palette::AtomText, color);


  // Get the y position of the mass
  int nameY = (50 - KDFont::SmallFont->glyphSize().height() * 2) / 2;
  int massY = nameY + KDFont::SmallFont->glyphSize().height();

  // Draw the mass of the atom
  char mass[12];
  Poincare::Number::FloatNumber(m_atom.mass).serialize(mass, 12, Poincare::Preferences::PrintFloatMode::Decimal, 12);
  coordonates = KDPoint(bounds().left() + 60, massY);
  ctx->drawString(mass, coordonates, KDFont::SmallFont, Palette::AtomText, Palette::BackgroundApps);
}

int atomInfo::numberOfSubviews() const {
  return 1;
}

View * atomInfo::subviewAtIndex(int index) {
  assert(index == 0);
  return &m_atomName;
}

void atomInfo::layoutSubviews(bool force) {
  // Get the y position of the name
  int nameY = (50 - KDFont::SmallFont->glyphSize().height() * 2) / 2;
  m_atomName.setFrame(KDRect(KDPoint(60, nameY), KDSize(bounds().width() - 60, KDFont::SmallFont->glyphSize().height())), force);
}

void atomInfo::setAtom(AtomDef atom) {
  m_atom = atom;
  m_atomName.setMessage(atom.name);
  markRectAsDirty(bounds());
}

KDSize atomInfo::minimalSizeForOptimalDisplay() const {
  return KDSize(150, 50);
}

}

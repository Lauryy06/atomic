#include "table_lines_view.h"
#include <escher/palette.h>

namespace Atomic {

tableLinesView::tableLinesView() :
  View()
{
}

void tableLinesView::drawRect(KDContext * ctx, KDRect rect) const {
  KDColor color = Palette::AtomTableLines;

  // Draw the lines that goes from the Barium to the Lanthanum
  // Vertical line:
  ctx->fillRect(KDRect(KDPoint(bounds().left() + 10, bounds().top()), KDSize(2, 50)), color);

  // Top horizontal line:
  ctx->fillRect(KDRect(KDPoint(bounds().left(), bounds().top()), KDSize(10, 2)), color);

  // Bottom horizontal line:
  ctx->fillRect(KDRect(KDPoint(bounds().left() + 10, bounds().top() + 48), KDSize(10, 2)), color);

  // Draw the lines that goes from the Radium to the Actinium
  // Vertical line:
  ctx->fillRect(KDRect(KDPoint(bounds().left() + 5, bounds().top() + 17), KDSize(2, 50)), color);

  // Top horizontal line:
  ctx->fillRect(KDRect(KDPoint(bounds().left(), bounds().top() + 17), KDSize(5, 2)), color);

  // Bottom horizontal line:
  ctx->fillRect(KDRect(KDPoint(bounds().left() + 5, bounds().top() + 65), KDSize(12, 2)), color);
}

KDSize tableLinesView::minimalSizeForOptimalDisplay() const {
  return KDSize(17, 69);
}

}

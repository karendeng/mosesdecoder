/*
 * InputPath.cpp
 *
 *  Created on: 23 Oct 2015
 *      Author: hieu
 */
#include <boost/foreach.hpp>
#include "InputPath.h"
#include "TargetPhrases.h"
#include "../TranslationModel/PhraseTable.h"

namespace Moses2
{
InputPath::InputPath(MemPool &pool, const SubPhrase<Moses2::Word> &subPhrase,
    const Range &range, size_t numPt, const InputPath *prefixPath)
:InputPathBase(pool, range, numPt, prefixPath)
,m_numRules(0)
,subPhrase(subPhrase)
{
  targetPhrases = pool.Allocate<const TargetPhrases*>(numPt);
  Init<const TargetPhrases*>(targetPhrases, numPt, NULL);
}

InputPath::~InputPath()
{
  // TODO Auto-generated destructor stub
}

void InputPath::AddTargetPhrases(const PhraseTable &pt,
    const TargetPhrases *tps)
{
  size_t ptInd = pt.GetPtInd();
  targetPhrases[ptInd] = tps;

  if (tps) {
    m_numRules += tps->GetSize();
  }
}

const TargetPhrases *InputPath::GetTargetPhrases(const PhraseTable &pt) const
{
  size_t ptInd = pt.GetPtInd();
  return targetPhrases[ptInd];
}

void InputPath::Debug(std::ostream &out, const System &system) const
{
  out << range << " ";
  subPhrase.Debug(out, system);
}

}


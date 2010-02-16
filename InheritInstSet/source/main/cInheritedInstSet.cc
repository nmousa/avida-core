/*
 *  cInheritedInstSet.cpp
 *  Avida
 *
 *  Created by Matthew Rupp on 1/4/10.
 *  Copyright 2010 Michigan State University. All rights reserved.
 *
 */

#include "cInheritedInstSet.h"
#include "cInstSet.h"
#include "cRandom.h"
#include "cWorld.h"
#include <cassert>


cInheritedInstSet::cInheritedInstSet(const cInheritedInstSet* in) : cInstSet(*in)
{
  m_allowed_redundancies = in->m_allowed_redundancies;
}


cInheritedInstSet::cInheritedInstSet(const cInstSet* in, tArray< tArray<int> >& allowed_redundancies) : cInstSet(*in)
{
  m_allowed_redundancies = allowed_redundancies;
}

cInheritedInstSet::cInheritedInstSet(const cInstSet* in, int init_val, const tArray< tArray<int> >& allowed_redundancies) : cInstSet(*in)
{
  m_allowed_redundancies = allowed_redundancies;
  if (init_val == 0)
    InitRedRandomly();
  else if (init_val > 0)
    InitRedByValue(init_val);
  Sync();
}



void cInheritedInstSet::InitRedRandomly()
{
  for (int x = 0; x < m_lib_name_map.GetSize(); x++)
    m_lib_name_map[x].redundancy = GetRandomRedundancy(x);
  return;
}



void cInheritedInstSet::InitRedByValue(int val)
{
  for (int x = 0; x < m_lib_name_map.GetSize(); x++){
    m_lib_name_map[x].redundancy = GetRandomRedundancy(x);
  }
  return;
}



bool cInheritedInstSet::MutateAllInsts(double p)
{
  bool did_mutate = false;
  for (int id = 0; id < m_lib_name_map.GetSize(); id++)
    if (RandProceed(p)){
      m_lib_name_map[id].redundancy = GetRandomRedundancy(id);
      did_mutate = true;
    }
  return did_mutate;
}


bool cInheritedInstSet::MutateSingleInst(double p)
{
  if (!RandProceed(p))
    return false;
  int id = m_world->GetRandom().GetUInt(0,m_lib_name_map.GetSize());
  m_lib_name_map[id].redundancy = GetRandomRedundancy(id);
  return true;
}



void cInheritedInstSet::Sync()
{
  int sum = 0;
  for (int x = 0; x < m_lib_name_map.GetSize(); x++)
    sum += m_lib_name_map[x].redundancy;
  assert(sum <= 255);
  m_mutation_chart = tArray<int>(sum, -1);
  int ndx = 0;
  for (int id = 0; id < m_lib_name_map.GetSize(); id++)
    for (int n = 0; n < m_lib_name_map[id].redundancy; n++)
      m_mutation_chart[ndx++] = id;
}



inline bool cInheritedInstSet::RandProceed(double p){
  return (m_world->GetRandom().GetDouble(0,1) < p);
}



inline int cInheritedInstSet::GetRandomRedundancy(int id){
  return m_allowed_redundancies[id][m_world->GetRandom().GetUInt(0,m_allowed_redundancies[id].GetSize())];
}




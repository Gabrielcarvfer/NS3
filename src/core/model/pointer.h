/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#pragma once

#include "attribute.h"
#include "object.h"

/**
 * \file
 * \ingroup attribute_Pointer
 * ns3::PointerValue attribute value declarations and template implementations.
 */

namespace ns3 {

//  Additional docs for class PointerValue:
/** Hold objects of type Ptr<T>. */
class PointerValue : public AttributeValue
{
public:
  PointerValue ();
  
  /**
   * Construct this PointerValue by referencing an explicit Object.
   *
   * \param [in] object The object to begin with.
   */
  PointerValue (Ptr<Object> object);

  /**
   * Set the value from by reference an Object.
   *
   * \param [in] object The object to reference.
   */
  void SetObject (Ptr<Object> object);

  /**
   * Get the Object referenced by the PointerValue.
   * \returns The Object.
   */
  Ptr<Object> GetObject (void) const;

  /**
   * Construct this PointerValue by referencing an explicit Object.
   *
   * \tparam T \deduced The type of the object.
   * \param [in] object The object to begin with.
   */
  template <typename T>
  PointerValue (const Ptr<T> & object);

  /**
   * Cast to an Object of type \c T.
   * \tparam T \explicit The type to cast to.
   */ 
  template <typename T>
  operator Ptr<T> () const;

  // Documentation generated by print-introspected-doxygen.cc
  template <typename T>
  void Set (const Ptr<T> & value);

  /** \tparam T \explicit The type to cast to. */
  template <typename T>
  Ptr<T> Get (void) const;

  template <typename T>
  bool GetAccessor (Ptr<T> &value) const;

  virtual Ptr<AttributeValue> Copy (void) const;
  virtual std::string SerializeToString (Ptr<const AttributeChecker> checker) const;
  virtual bool DeserializeFromString (std::string value, Ptr<const AttributeChecker> checker);

private:
  Ptr<Object> m_value;
};


class PointerChecker : public AttributeChecker 
{
public:

  /**
   * Get the TypeId of the base type.
   * \returns The base TypeId.
   */
  virtual TypeId GetPointeeTypeId (void) const = 0;
};
  
/**
 * Create a PointerChecker for a type.
 * \tparam T \explicit The underlying type.
 * \returns The PointerChecker.
 */
template <typename T>
Ptr<AttributeChecker> MakePointerChecker (void);

} // namespace ns3



/***************************************************************
 *  Implementation of the templates declared above.
 ***************************************************************/

namespace ns3 {

namespace internal {

/** PointerChecker implementation. */
template <typename T>
class PointerChecker : public ns3::PointerChecker
{
  virtual bool Check (const AttributeValue &val) const {
    const PointerValue *value = dynamic_cast<const PointerValue *> (&val);
    if (value == 0)
      {
        return false;
      }
    if (value->GetObject () == 0)
      {
        return true;
      }
    T *ptr = dynamic_cast<T*> (PeekPointer (value->GetObject ()));
    if (ptr == 0)
      {
        return false;
      }
    return true;
  }
  virtual std::string GetValueTypeName (void) const {
    return "ns3::PointerValue";
  }
  virtual bool HasUnderlyingTypeInformation (void) const {
    return true;
  }
  virtual std::string GetUnderlyingTypeInformation (void) const {
    TypeId tid = T::GetTypeId ();
    return "ns3::Ptr< " + tid.GetName () + " >";
  }
  virtual Ptr<AttributeValue> Create (void) const {
    return ns3::Create<PointerValue> ();
  }
  virtual bool Copy (const AttributeValue &source, AttributeValue &destination) const {
    const PointerValue *src = dynamic_cast<const PointerValue *> (&source);
    PointerValue *dst = dynamic_cast<PointerValue *> (&destination);
    if (src == 0 || dst == 0)
      {
        return false;
      }
    *dst = *src;
    return true;
  }
  virtual TypeId GetPointeeTypeId (void) const {
    return T::GetTypeId ();
  }
};

} // namespace internal

template <typename T>
PointerValue::PointerValue (const Ptr<T> &object)
{
  m_value = object;
}

template <typename T>
void 
PointerValue::Set (const Ptr<T> &object)
{
  m_value = object;
}

template <typename T>
Ptr<T> 
PointerValue::Get (void) const
{
  T *v = dynamic_cast<T *> (PeekPointer (m_value));
  return v;
}

template <typename T>
PointerValue::operator Ptr<T> () const
{
  return Get<T> ();
}

template <typename T>
bool 
PointerValue::GetAccessor (Ptr<T> &v) const
{
  Ptr<T> ptr = dynamic_cast<T*> (PeekPointer (m_value));
  if (ptr == 0)
    {
      return false;
    }
  v = ptr;
  return true;
}


ATTRIBUTE_ACCESSOR_DEFINE (Pointer);

template <typename T>
Ptr<AttributeChecker>
MakePointerChecker (void)
{
  return Create<internal::PointerChecker<T> > ();
}


} // namespace ns3



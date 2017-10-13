/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#include "ns3/core-module.h"
#include "ns3/config-store-module.h"

#include <iostream>

using namespace ns3;

/**
 * \ingroup configstore-examples
 * \ingroup examples
 *
 * \brief Example class to demonstrate use of the ns-3 Config Store
 */
class ConfigExample : public Object
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void) {
    static TypeId tid = TypeId ("ns3::ConfigExample")
      .SetParent<Object> ()
      .AddAttribute ("TestInt16", "help text",
                     IntegerValue (-2),
                     MakeIntegerAccessor (&ConfigExample::m_int16),
                     MakeIntegerChecker<int16_t> ())
      ;
      return tid;
    }
  int16_t m_int16; ///< value to configure
};

NS_OBJECT_ENSURE_REGISTERED (ConfigExample);

// Assign a new default value to A::TestInt16 (-5)
// Configure a TestInt16 value for a special instance of A (to -3)
// View the output from the config store
// 
int main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);
  
  Config::SetDefault ("ns3::ConfigExample::TestInt16", IntegerValue (-5));

  Ptr<ConfigExample> a_obj = CreateObject<ConfigExample> ();
  NS_ABORT_MSG_UNLESS (a_obj->m_int16 == -5, "Cannot set ConfigExample's integer attribute via Config::SetDefault");

  Ptr<ConfigExample> b_obj = CreateObject<ConfigExample> ();
  b_obj->SetAttribute ("TestInt16", IntegerValue (-3));
  IntegerValue iv;
  b_obj->GetAttribute ("TestInt16", iv);
  NS_ABORT_MSG_UNLESS (iv.Get () == -3, "Cannot set ConfigExample's integer attribute via SetAttribute");

  // These test objects are not rooted in any ns-3 configuration namespace.
  // This is usually done automatically for ns3 nodes and channels, but
  // we can establish a new root and anchor one of them there (note; we 
  // can't use two objects of the same type as roots).  Rooting one of these
  // is necessary for it to show up in the config namespace so that
  // ConfigureAttributes() will work below.
  Config::RegisterRootNamespaceObject (b_obj);
  
#ifdef HAVE_LIBXML2
  // Output config store to XML format
  Config::SetDefault ("ns3::ConfigStore::Filename", StringValue ("output-attributes.xml"));
  Config::SetDefault ("ns3::ConfigStore::FileFormat", StringValue ("Xml"));
  Config::SetDefault ("ns3::ConfigStore::Mode", StringValue ("Save"));
  ConfigStore outputConfig;
  outputConfig.ConfigureDefaults ();
  outputConfig.ConfigureAttributes ();
#endif /* HAVE_LIBXML2 */

  // Output config store to txt format
  Config::SetDefault ("ns3::ConfigStore::Filename", StringValue ("output-attributes.txt"));
  Config::SetDefault ("ns3::ConfigStore::FileFormat", StringValue ("RawText"));
  Config::SetDefault ("ns3::ConfigStore::Mode", StringValue ("Save"));
  ConfigStore outputConfig2;
  outputConfig2.ConfigureDefaults ();
  outputConfig2.ConfigureAttributes ();
 
  Simulator::Run ();

  Simulator::Destroy ();
}

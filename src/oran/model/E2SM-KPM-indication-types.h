//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 27/10/22.
//

#ifndef NS3_E2SM_KPM_INDICATION_TYPES_H_
#define NS3_E2SM_KPM_INDICATION_TYPES_H_

/**
 * \ingroup oran
 * E2SM KPM indication types and format declarations.
 */

namespace ns3
{
namespace oran
{
// O-RAN WG3 ES2M KPM v02.00.03
/**
 * \brief E2SM KPM Indication formats
 */
enum KPM_INDICATION_FORMATS
{
    KPM_INDICATION_FORMAT_1 = 1,
    KPM_INDICATION_FORMAT_2,
    KPM_INDICATION_FORMAT_3
};
} // namespace oran
} // namespace ns3
#endif // NS3_E2SM_KPM_INDICATION_TYPES_H_

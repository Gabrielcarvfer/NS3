#Source: https://www.saulodamata.com/codes/86-voip-traffic-generator-for-ns-3.html

set(contrib_name sauloDaMata)
set(contribution_lib_components
        voip
        )

build_contrib_lib("${contrib_name}" "${contribution_lib_components}")

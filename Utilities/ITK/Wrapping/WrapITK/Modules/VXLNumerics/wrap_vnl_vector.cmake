# auto include feature must be disable because the class is not in the file
# with the same name
SET(WRAPPER_AUTO_INCLUDE_HEADERS OFF)
WRAP_INCLUDE("vcl_complex.h")
WRAP_INCLUDE("vnl/vnl_matrix.h")
WRAP_INCLUDE("vnl/vnl_vector.h")

WRAP_CLASS("vnl_vector")
  WRAP_TEMPLATE("${ITKM_D}" "${ITKT_D}")
  WRAP_TEMPLATE("_vcl_complex${ITKM_D}" "vcl_complex<${ITKT_D}>")
  WRAP_TEMPLATE("${ITKM_F}" "${ITKT_F}")
  WRAP_TEMPLATE("_vcl_complex${ITKM_F}" "vcl_complex<${ITKT_F}>")
  WRAP_TEMPLATE("${ITKM_SI}" "${ITKT_SI}")
  WRAP_TEMPLATE("${ITKM_SL}" "${ITKT_SL}")
  WRAP_TEMPLATE("${ITKM_LD}" "${ITKT_LD}")
  WRAP_TEMPLATE("_vcl_complex${ITKM_LD}" "vcl_complex<${ITKT_LD}>")
  WRAP_TEMPLATE("${ITKM_SC}" "${ITKT_SC}")
  WRAP_TEMPLATE("${ITKM_UC}" "un${ITKT_SC}")
  WRAP_TEMPLATE("${ITKM_UI}" "un${ITKT_SI}")
  WRAP_TEMPLATE("${ITKM_UL}" "un${ITKT_SL}")
END_WRAP_CLASS()

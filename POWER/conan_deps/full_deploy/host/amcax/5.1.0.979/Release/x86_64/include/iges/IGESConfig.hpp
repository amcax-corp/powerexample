/// @file      IGESConfig.hpp
/// @brief     IGES API Config Macro Define
/// @details   there are two configurations included. One is FACE_MODE and BREP_MODE that take effect for all writes. 
/// Another type is the WRITE_ATTR_XXX configuration that takes effect only for the FACE_MODE of the Label's Write
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.

#pragma once

/// @brief  The FACE_MODE macro is only applicable to the IGES::IgesIO::Write interface. 
/// and BREP_MODE represent two different model expression forms. Please note that FACE_MODE 
/// is suitable for pure geometric scenarios. Therefore, iges files written in FACE_MODE may 
/// not be 100% restored when read back. If 100% restoration is required, it is recommended to apply the configuration of BREP_MODE
#define FACE_MODE (0 << 0)

/// @brief The BREP_MODE macro is only applicable to the IGES::IgesIO::Write interface. 
/// It uses the 186 entities in the IGES standard to fully express topological information. 
/// Therefore, compared with the FACE_MODE configuration, it is more suitable for scenarios
/// with complex topologies, such as if necessary Please give priority to using the BREP_MODE macro for Write whenever possible
#define BREP_MODE (1 << 0)





/// @brief This configurations are only applicable to IGES::IgesIO::Write(Label&, Face_Mode| XXXX) form, 
/// any other combination, this configuration does not take effect. 
/// WRITE_ATTR_DEFAULT represents the default attribute control form, which is currently equivalent to WRITE_ATTR_SELF_HIGH_PRI.
#define WRITE_ATTR_DEFAULT       (0 << 1)

/// @brief This configurations are only applicable to IGES::IgesIO::Write(Label&, Face_Mode| XXXX) form, 
/// any other combination, this configuration does not take effect. 
/// WRITE_ATTR_NOT_INHERIT represents that the properties of the parent topology do not affect the child topology
#define WRITE_ATTR_NOT_INHERIT   (1 << 1)

/// @brief This configurations are only applicable to IGES::IgesIO::Write(Label&, Face_Mode| XXXX) form, 
/// any other combination, this configuration does not take effect. 
/// This configuration item only takes effect when there is a conflict in the assignment of attributes. 
/// When there is no conflict, it automatically inherits the attributes of the parent topology 
/// WRITE_ATTR_SELF_HIGH_PRI represents the high priority of the subtopology and gives priority to choosing its own attributes
#define WRITE_ATTR_SELF_HIGH_PRI (2 << 1)

/// @brief This configurations are only applicable to IGES::IgesIO::Write(Label&, Face_Mode| XXXX) form,
/// any other combination, this configuration does not take effect. 
/// This configuration item only takes effect when there is a conflict in the assignment of attributes. 
/// When there is no conflict, it automatically inherits the attributes of the parent topology 
/// WRITE_ATTR_SELF_LOW_PRI represents the high priority of the parent topology, and the parent topology attribute is preferred
#define WRITE_ATTR_SELF_LOW_PRI  (3 << 1)

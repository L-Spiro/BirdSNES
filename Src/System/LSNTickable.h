/**
 * Copyright L. Spiro 2026
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The base class for a tickable system component.
 */


#pragma once

#include "../LSNBirdSNES.h"


namespace lsn {

	/**
	 * Class CRicoh5A22
	 * \brief The base class for a tickable system component.
	 *
	 * Description: The base class for a tickable system component.
	 */
	class CTickable {
	public :
		// == Types.



		// == Functions.
		/**
		 * Gets the master-clock speed.
		 * 
		 * \return Returns the master-clock speed.
		 **/
		inline uint64_t							MasterClock() const { return m_ui64MasterClock; }

		/**
		 * Gets the master divisor.
		 * 
		 * \return Returns the master divisor.
		 **/
		inline uint64_t							MasterDivisor() const { return m_ui64MasterDiv; }

		/**
		 * Gets the current clock divisor.
		 * 
		 * \return Returns the current clock divisor.
		 **/
		inline uint8_t							Divisor() const { return m_ui8Speed; }


	protected :
		// == Members.
		uint64_t								m_ui64MasterClock = 0;										/**< The master clock. */
		uint64_t								m_ui64MasterDiv = 0;										/**< The master divisor. */
		uint8_t									m_ui8Speed = 6;												/**< The current divisor. */

	};

}	// namespace lsn

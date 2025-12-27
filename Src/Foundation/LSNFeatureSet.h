/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Detects the processor feature set.
 */

#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <string>
#if defined( _MSC_VER )
#include <intrin.h>
#elif defined( __i386__ ) || defined( __x86_64__ )
#include <cpuid.h>
#else
//#include <x86intrin.h>
#endif  // #if defined( __i386__ ) || defined( __x86_64__ )


#if (!defined( __APPLE__ ) && (defined( __i386__ ) || defined( __x86_64__ ))) || defined( _MSC_VER )
#define NN9_CPUID
#ifdef __GNUC__
void __cpuid( int * _piCpuInfo, int _iInfo ) {
	__asm__ __volatile__(
		"xchg %%ebx, %%edi;"
		"cpuid;"
		"xchg %%ebx, %%edi;"
		:"=a" (_piCpuInfo[0]), "=D" (_piCpuInfo[1]), "=c" (_piCpuInfo[2]), "=d" (_piCpuInfo[3])
		:"0" (_iInfo)
	);
}

unsigned long long _xgetbv( unsigned int _uiIndex ) {
	unsigned int eax, edx;
	__asm__ __volatile__(
		"xgetbv;"
		: "=a" (eax), "=d"(edx)
		: "c" (_uiIndex)
	);
	return ((unsigned long long)edx << 32) | eax;
}

void __cpuidex( int * _piCpuInfo, int _iInfo, int _iSubFunc ) {
	// _iInfo is the leaf, and _iSubFunc is the sub-leaf.
	__cpuid_count( _iInfo, _iSubFunc, _piCpuInfo[0], _piCpuInfo[1], _piCpuInfo[2], _piCpuInfo[3] );
}
#endif	// #ifdef __GNUC__
#else
#include <sys/sysctl.h>
#endif	// #if (!defined( __APPLE__ ) && (defined( __i386__ ) || defined( __x86_64__ ))) || defined( _MSC_VER )


namespace nn9 {
#ifdef NN9_CPUID
	/**
	 * Class FeatureSet
	 * \brief Detects the processor feature set.
	 *
	 * Description: Detects the processor feature set.
	 */
	class FeatureSet {
		class									InstructionSet_Internal;

	public :
		// == Functions.
		static std::string						Vendor() { return m_iiCpuRep.m_sVendor; }
		static std::string						Brand() { return m_iiCpuRep.m_sBrand; }

		static bool								SSE3() { return m_iiCpuRep.m_bEcx1[0]; }
		static bool								PCLMULQDQ() { return m_iiCpuRep.m_bEcx1[1]; }
		static bool								MONITOR() { return m_iiCpuRep.m_bEcx1[3]; }
		static bool								SSSE3() { return m_iiCpuRep.m_bEcx1[9]; }
		static bool								FMA() { return m_iiCpuRep.m_bEcx1[12]; }
		static bool								CMPXCHG16B() { return m_iiCpuRep.m_bEcx1[13]; }
		static bool								SSE41() { return m_iiCpuRep.m_bEcx1[19]; }
		static bool								SSE42() { return m_iiCpuRep.m_bEcx1[20]; }
		static bool								MOVBE() { return m_iiCpuRep.m_bEcx1[22]; }
		static bool								POPCNT() { return m_iiCpuRep.m_bEcx1[23]; }
		static bool								AES() { return m_iiCpuRep.m_bEcx1[25]; }
		static bool								XSAVE() { return m_iiCpuRep.m_bEcx1[26]; }
		static bool								OSXSAVE() { return m_iiCpuRep.m_bEcx1[27]; }
		static bool								AVX() { return m_iiCpuRep.m_bEcx1[28]; }
		static bool								F16C() { return m_iiCpuRep.m_bEcx1[29]; }
		static bool								RDRAND() { return m_iiCpuRep.m_bEcx1[30]; }
			
		static bool								MSR() { return m_iiCpuRep.m_bEdx1[5]; }
		static bool								CX8() { return m_iiCpuRep.m_bEdx1[8]; }
		static bool								SEP() { return m_iiCpuRep.m_bEdx1[11]; }
		static bool								CMOV() { return m_iiCpuRep.m_bEdx1[15]; }
		static bool								CLFSH() { return m_iiCpuRep.m_bEdx1[19]; }
		static bool								MMX() { return m_iiCpuRep.m_bEdx1[23]; }
		static bool								FXSR() { return m_iiCpuRep.m_bEdx1[24]; }
		static bool								SSE() { return m_iiCpuRep.m_bEdx1[25]; }
		static bool								SSE2() { return m_iiCpuRep.m_bEdx1[26]; }

		static bool								FSGSBASE() { return m_iiCpuRep.m_bEbx7[0]; }
		static bool								BMI1() { return m_iiCpuRep.m_bEbx7[3]; }
		static bool								HLE() { return m_iiCpuRep.m_bIsIntel && m_iiCpuRep.m_bEbx7[4]; }
		static bool								AVX2() { return m_iiCpuRep.m_bEbx7[5]; }
		static bool								BMI2() { return m_iiCpuRep.m_bEbx7[8]; }
		static bool								ERMS() { return m_iiCpuRep.m_bEbx7[9]; }
		static bool								INVPCID() { return m_iiCpuRep.m_bEbx7[10]; }
		static bool								RTM() { return m_iiCpuRep.m_bIsIntel && m_iiCpuRep.m_bEbx7[11]; }
		static bool								AVX512F() { return m_iiCpuRep.m_bEbx7[16]; }
		static bool								RDSEED() { return m_iiCpuRep.m_bEbx7[18]; }
		static bool								ADX() { return m_iiCpuRep.m_bEbx7[19]; }
		static bool								AVX512PF() { return m_iiCpuRep.m_bEbx7[26]; }
		static bool								AVX512ER() { return m_iiCpuRep.m_bEbx7[27]; }
		static bool								AVX512CD() { return m_iiCpuRep.m_bEbx7[28]; }
		static bool								SHA() { return m_iiCpuRep.m_bEbx7[29]; }

		static bool								AVX512BW() { return m_iiCpuRep.m_bEbx7[30]; }
		static bool								AVX512VL() { return m_iiCpuRep.m_bEbx7[31]; }
		static bool								AVX512BF16() { return m_iiCpuRep.m_bEax7_1[5]; }
		static bool								AVX_VNNI() { return m_iiCpuRep.m_bEbx7_1[11];  }

		static bool								PREFETCHWT1() { return m_iiCpuRep.m_bEcx7[0]; }

		static bool								LAHF() { return m_iiCpuRep.m_bEcx81[0]; }
		static bool								LZCNT() { return m_iiCpuRep.m_bIsIntel && m_iiCpuRep.m_bEcx81[5]; }
		static bool								ABM() { return m_iiCpuRep.m_bIsAmd && m_iiCpuRep.m_bEcx81[5]; }
		static bool								SSE4a() { return m_iiCpuRep.m_bIsAmd && m_iiCpuRep.m_bEcx81[6]; }
		static bool								XOP() { return m_iiCpuRep.m_bIsAmd && m_iiCpuRep.m_bEcx81[11]; }
		static bool								TBM() { return m_iiCpuRep.m_bIsAmd && m_iiCpuRep.m_bEcx81[21]; }

		static bool								SYSCALL() { return m_iiCpuRep.m_bIsIntel && m_iiCpuRep.m_bEdx81[11]; }
		static bool								MMXEXT() { return m_iiCpuRep.m_bIsAmd && m_iiCpuRep.m_bEdx81[22]; }
		static bool								RDTSCP() { return m_iiCpuRep.m_bIsIntel && m_iiCpuRep.m_bEdx81[27]; }
		static bool								_3DNOWEXT() { return m_iiCpuRep.m_bIsAmd && m_iiCpuRep.m_bEdx81[30]; }
		static bool								_3DNOW() { return m_iiCpuRep.m_bIsAmd && m_iiCpuRep.m_bEdx81[31]; }





		// ARM/Apple Silicon Features.
		static constexpr  bool					NEON() { return false; }
		static constexpr  bool					SVE() { return false; }
		static constexpr  bool					CRC32() { return false; }
		static constexpr  bool					ASIMD() { return false; }
		static constexpr  bool					FP16() { return false; }
		static constexpr  bool					ATOMIC() { return false; }
		static constexpr  bool					BF16() { return false; }
		static constexpr  bool					RDMA() { return false; }

		// Additional ARM-specific capabilities.
		static constexpr  bool					DotProd() { return false; }
		static constexpr  bool					FP() { return false; }
		static constexpr  bool					SHA1() { return false; }
		static constexpr  bool					SHA256() { return false; }
		static constexpr  bool					SHA512() { return false; }

	private :
		// == Members.
		static const InstructionSet_Internal	m_iiCpuRep;


		// == Types.
		class InstructionSet_Internal {
		public :
			InstructionSet_Internal() :
				m_iNumIds{ 0 },
				m_iNumExIds{ 0 },
				m_bIsIntel{ false },
				m_bIsAmd{ false },
				m_bEcx1{ 0 },
				m_bEdx1{ 0 },
				m_bEbx7{ 0 },
				m_bEcx7{ 0 },
				m_bEcx81{ 0 },
				m_bEdx81{ 0 },
				m_vData{},
				m_vExtData{} {
				//int cpuInfo[4] = {-1};
				std::array<int, 4> aCpuI;

				// Calling __cpuid with 0x0 as the function_id argument
				// gets the number of the highest valid function ID.
				__cpuid( aCpuI.data(), 0 );
				m_iNumIds = aCpuI[0];

				for ( int I = 0; I <= m_iNumIds; ++I ) {
					__cpuidex( aCpuI.data(), I, 0 );
					m_vData.push_back( aCpuI );
				}

				// Capture cVendor string
				char cVendor[0x20];
				::memset( cVendor, 0, sizeof( cVendor ) );
				(*reinterpret_cast<int*>(cVendor)) = m_vData[0][1];
				(*reinterpret_cast<int*>(cVendor + 4)) = m_vData[0][3];
				(*reinterpret_cast<int*>(cVendor + 8)) = m_vData[0][2];
				m_sVendor = cVendor;
				if ( m_sVendor == "GenuineIntel" ) {
					m_bIsIntel = true;
				}
				else if ( m_sVendor == "AuthenticAMD" ) {
					m_bIsAmd = true;
				}

				// load bitset with flags for function 0x00000001
				if ( m_iNumIds >= 1 ) {
					m_bEcx1 = m_vData[1][2];
					m_bEdx1 = m_vData[1][3];
				}

				// load bitset with flags for function 0x00000007
				if ( m_iNumIds >= 7 ) {
					m_bEbx7 = m_vData[7][1];
					m_bEcx7 = m_vData[7][2];
				}

				// Query CPUID.(EAX=07H, ECX=1) for AVX-512 BF16 support
				if ( m_iNumIds >= 7 ) {
					std::array<int, 4> aCpuI2;
					__cpuidex( aCpuI2.data(), 7, 1 );
					m_bEax7_1 = aCpuI2[0];
					m_bEbx7_1 = aCpuI2[1];
					m_bEcx7_1 = aCpuI2[2];
					m_bEdx7_1 = aCpuI2[3];
				}

				// Calling __cpuid with 0x80000000 as the function_id argument
				// gets the number of the highest valid extended ID.
				__cpuid( aCpuI.data(), 0x80000000 );
				m_iNumExIds = aCpuI[0];

				char cBrand[0x40];
				::memset( cBrand, 0, sizeof( cBrand ) );

				for ( int I = 0x80000000; I <= m_iNumExIds; ++I ) {
					__cpuidex( aCpuI.data(), I, 0 );
					m_vExtData.push_back( aCpuI );
				}

				// load bitset with flags for function 0x80000001
				if ( m_iNumExIds >= 0x80000001 ) {
					m_bEcx81 = m_vExtData[1][2];
					m_bEdx81 = m_vExtData[1][3];
				}

				// Interpret CPU cBrand string if reported
				if ( m_iNumExIds >= 0x80000004 ) {
					::memcpy( cBrand, m_vExtData[2].data(), sizeof( aCpuI ) );
					::memcpy( cBrand + 16, m_vExtData[3].data(), sizeof( aCpuI ) );
					::memcpy( cBrand + 32, m_vExtData[4].data(), sizeof( aCpuI ) );
					m_sBrand = cBrand;
				}
			};


			// == Members.
			std::string							m_sVendor;
			std::string							m_sBrand;
			int									m_iNumIds;
			int									m_iNumExIds;
            
			std::bitset<32>						m_bEcx1;
			std::bitset<32>						m_bEdx1;
			std::bitset<32>						m_bEbx7;
			std::bitset<32>						m_bEcx7;

			std::bitset<32>						m_bEax7_1;
			std::bitset<32>						m_bEbx7_1;
			std::bitset<32>						m_bEcx7_1;
			std::bitset<32>						m_bEdx7_1;

			std::bitset<32>						m_bEcx81;
			std::bitset<32>						m_bEdx81;
			std::vector<std::array<int, 4>>		m_vData;
			std::vector<std::array<int, 4>>		m_vExtData;

			bool								m_bIsIntel;
			bool								m_bIsAmd;
		};
	};
#else
	/**
	 * Class FeatureSet
	 * \brief Detects the processor feature set.
	 *
	 * Description: Detects the processor feature set.
	 */
	class FeatureSet {
	public :
		// General
		static std::string						Vendor() {
			static std::string sVendor = GetSysctlString( "machdep.cpu.vendor" );
			return sVendor;
		}

		static std::string						Brand() {
			static std::string sBrand = GetSysctlString( "machdep.cpu.brand_string" );
			return sBrand;
		}

		// x86 Features.
		static bool 							SSE3() { return HasFeature( "machdep.cpu.features", "SSE3" ); }
		static bool								PCLMULQDQ() { return HasFeature( "machdep.cpu.features", "PCLMULQDQ" ); }
		static bool								MONITOR() { return HasFeature( "machdep.cpu.features", "MONITOR" ); }
		static bool								SSSE3() { return HasFeature( "machdep.cpu.features", "SSSE3" ); }
		static bool								FMA() { return HasFeature( "machdep.cpu.features", "FMA" ); }
		static bool								CMPXCHG16B() { return HasFeature( "machdep.cpu.features", "CMPXCHG16B" ); }
		static bool								SSE41() { return HasFeature( "machdep.cpu.features", "SSE4.1" ); }
		static bool								SSE42() { return HasFeature( "machdep.cpu.features", "SSE4.2" ); }
		static bool								AVX() { return HasFeature( "machdep.cpu.features", "AVX" ); }
		static bool								AVX2() { return HasFeature( "machdep.cpu.extfeatures", "AVX2" ); }
		static bool								AES() { return HasFeature( "machdep.cpu.features", "AES" ); }

		// ARM/Apple Silicon Features.
		static bool								NEON() { return IsARM() && HasFeature( "hw.optional.neon" ); }
		static bool								SVE() { return IsARM() && HasFeature( "hw.optional.sve" ); }
		static bool								CRC32() { return IsARM() && HasFeature( "hw.optional.armv8_crc32" ); }
		static bool								ASIMD() { return IsARM() && HasFeature( "hw.optional.asimd" ); }
		static bool								FP16() { return IsARM() && HasFeature( "hw.optional.armv8_2_fhm" ); }
		static bool								ATOMIC() { return IsARM() && HasFeature( "hw.optional.armv8_1_atomics" ); }
		static bool								BF16() { return IsARM() && HasFeature( "hw.optional.armv8_6_bf16" ); }
		static bool								RDMA() { return IsARM() && HasFeature( "hw.optional.armv8_rdma" ); }

		// Additional ARM-specific capabilities.
		static bool								DotProd() { return IsARM() && HasFeature( "hw.optional.armv8_2_dotprod" ); }
		static bool								FP() { return IsARM() && HasFeature( "hw.optional.floatingpoint" ); }
		static bool								SHA1() { return IsARM() && HasFeature( "hw.optional.armv8_sha1" ); }
		static bool								SHA256() { return IsARM() && HasFeature( "hw.optional.armv8_sha256" ); }
		static bool								SHA512() { return IsARM() && HasFeature( "hw.optional.armv8_sha512" ); }


		
        static constexpr  bool					MOVBE() { return false; }
        static constexpr  bool					POPCNT() { return false; }
        static constexpr  bool					XSAVE() { return false; }
        static constexpr  bool					OSXSAVE() { return false; }
        static constexpr  bool					F16C() { return false; }
        static constexpr  bool					RDRAND() { return false; }

        static constexpr  bool					MSR() { return false; }
        static constexpr  bool					CX8() { return false; }
        static constexpr  bool					SEP() { return false; }
        static constexpr  bool					CMOV() { return false; }
        static constexpr  bool					CLFSH() { return false; }
        static constexpr  bool					MMX() { return false; }
        static constexpr  bool					FXSR() { return false; }
        static constexpr  bool					SSE() { return false; }
        static constexpr  bool					SSE2() { return false; }

        static constexpr  bool					FSGSBASE() { return false; }
        static constexpr  bool					BMI1() { return false; }
        static constexpr  bool					HLE() { return false; }
        static constexpr  bool					BMI2() { return false; }
        static constexpr  bool					ERMS() { return false; }
        static constexpr  bool					INVPCID() { return false; }
        static constexpr  bool					RTM() { return false; }
        static constexpr  bool					AVX512F() { return false; }
        static constexpr  bool					RDSEED() { return false; }
        static constexpr  bool					ADX() { return false; }
        static constexpr  bool					AVX512PF() { return false; }
        static constexpr  bool					AVX512ER() { return false; }
        static constexpr  bool					AVX512CD() { return false; }
        static constexpr  bool					SHA() { return false; }

        static constexpr  bool					AVX512BW() { return false; }
        static constexpr  bool					AVX512VL() { return false; }
        static constexpr  bool					AVX512BF16() { return false; }
		static constexpr  bool					AVX_VNNI() { return false; }

        static constexpr  bool					PREFETCHWT1() { return false; }

        static constexpr  bool					LAHF() { return false; }
        static constexpr  bool					LZCNT() { return false; }
        static constexpr  bool					ABM() { return false; }
        static constexpr  bool					SSE4a() { return false; }
        static constexpr  bool					XOP() { return false; }
        static constexpr  bool					TBM() { return false; }

        static constexpr  bool					SYSCALL() { return false; }
        static constexpr  bool					MMXEXT() { return false; }
        static constexpr  bool					RDTSCP() { return false; }
        static constexpr  bool					_3DNOWEXT() { return false; }
        static constexpr  bool					_3DNOW() { return false; }

	private :
		static std::string						GetSysctlString( const char * _pcName ) {
			size_t sSize = 0;
			::sysctlbyname( _pcName, nullptr, &sSize, nullptr, 0 );
			if ( sSize == 0 ) { return ""; }
			std::vector<char> buffer( sSize );
			::sysctlbyname( _pcName, buffer.data(), &sSize, nullptr, 0 );
			return std::string( buffer.data() );
		}

		static bool								HasFeature( const char * _pcSysCtlName, const char * _pcFeature ) {
			std::string pcFeatures = GetSysctlString( _pcSysCtlName );
			return pcFeatures.find( _pcFeature ) != std::string::npos;
		}

		static bool								HasFeature( const char * _pcFeature ) {
			int iValue = 0;
			size_t sSize = sizeof( iValue );
			if ( sysctlbyname( _pcFeature, &iValue, &sSize, nullptr, 0 ) == 0 ) {
				return iValue != 0;
			}
			return false;
		}

		static bool								IsARM() {
			static bool bIsArm =	GetSysctlString( "hw.machine" ).find( "arm" ) != std::string::npos ||
									GetSysctlString( "hw.machine" ).find( "aarch64" ) != std::string::npos;
			return bIsArm;
		}
	};
#endif	// #ifdef NN9_CPUID

}   // namespace nn9

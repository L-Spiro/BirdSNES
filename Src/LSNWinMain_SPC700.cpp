#ifdef _WIN32

#include "LSNBirdSNES.h"


#ifdef LSN_SPC700_CPU_VERIFY
#include "Files/LSNStdFile.h"


#include "Bus/LSNBusB.h"
#include "Cpu/SPC-700/LSNSpc700.h"
#include "LSONJson.h"


int WINAPI wWinMain( _In_ HINSTANCE /*_hInstance*/, _In_opt_ HINSTANCE /*_hPrevInstance*/, _In_ LPWSTR /*_lpCmdLine*/, _In_ int /*_nCmdShow*/ ) {
	std::unique_ptr<lsn::CBusB> pbBus = std::make_unique<lsn::CBusB>();
	pbBus->ApplyBasicMapping();
	std::unique_ptr<lsn::CSpc700> pcCpu = std::make_unique<lsn::CSpc700>( (*pbBus.get()) );
	//std::vector<uint8_t> vRam( 0x1000000 );
	//pbBus->SetMemory( vRam.data() );

	auto pRoot = GetThisPath().remove_filename();
	const std::filesystem::path pTests = std::filesystem::path( ".." ) / ".." / "Research" / "spc700" / "v1";
	{
		for ( uint32_t I = 0x2D; I < 0x2E; ++I ) {
			std::wstring wsFile;
			lson::CJson jSon;
			std::vector<uint8_t> vBytes;
			lsn::CStdFile sfFile;
			
			wchar_t wcFile[MAX_PATH];
			std::swprintf( wcFile, std::size( wcFile ), L"%.2X.json", I );
			const std::filesystem::path pFull = pRoot / pTests / wcFile;
				
			int32_t i32MinSize = INT32_MAX, i32MaxSize = 0;
			if ( sfFile.Open( pFull ) == lsn::LSN_E_SUCCESS ) {
				sfFile.LoadToMemory( vBytes );
				vBytes.push_back( 0 );

				if ( !jSon.SetJson( reinterpret_cast<const char *>(vBytes.data()) ) ) {
					lsn::DebugA( "JSON FAIL\r\n" );
				}
				else {
					pcCpu->Reset<true>();
					pbBus->ApplyBasicMapping();

					const lson::CJsonContainer::LSON_JSON_VALUE & jvRoot = jSon.GetContainer()->GetValue( jSon.GetContainer()->GetRoot() );
					for ( size_t J = 0; J < jvRoot.vArray.size(); ++J ) {
						const lson::CJsonContainer::LSON_JSON_VALUE & jvThis = jSon.GetContainer()->GetValue( jvRoot.vArray[J] );
							
						if ( J >= 900 && i32MinSize != lsn::CSpc700::InstrTable()[I].ui8TotalCycles && lsn::CSpc700::InstrTable()[I].iInstruction != lsn::CSpc700::LSN_I_BRA ) {
							lsn::DebugLine( std::format( "\r\n\r\n\r\n*** CHECK CYCLE COUNT {} -> {} ***\r\n\r\n\r\n\r\n\r\n", lsn::CSpc700::InstrTable()[I].ui8TotalCycles,
								i32MinSize ) );
						}

#ifdef LSN_SPC700_CYCLES_DOC
						if ( i32MinSize == i32MaxSize ) {
							lsn::DebugLine( std::format( "{} ({:02X})\tCycles: {}\tSize: {}\r\n"
							"\t{}\r\nCycle\tR/W\tDesc.", lsn::CSpc700::InstrTable()[I].pcName, I,
								i32MinSize,
								lsn::CSpc700::InstrTable()[I].ui8Size,
								lsn::CSpc700::InstrTable()[I].pcTypeString ) );
						}
						else {
							lsn::DebugLine( std::format( "{} ({:02X})\tCycles: {}-{}\tSize: {}\r\n"
							"\t{}\r\nCycle\tR/W\tDesc.", lsn::CSpc700::InstrTable()[I].pcName, I,
								i32MinSize, i32MaxSize,
								lsn::CSpc700::InstrTable()[I].ui8Size,
								lsn::CSpc700::InstrTable()[I].pcTypeString ) );
						}
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
						int32_t i32Cycles = pcCpu->RunJsonTest( jSon, jvThis );
						if ( i32Cycles > 0 ) {
							i32MinSize = std::min( i32MinSize, i32Cycles );
							i32MaxSize = std::max( i32MaxSize, i32Cycles );
						}
					}
#ifdef LSN_SPC700_CYCLES_DOC
					lsn::DebugLine( std::format( "Min: {}\tMax: {}", i32MinSize, i32MaxSize ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
					lsn::DebugA( "JSON NOT FAIL\r\n" );
					::OutputDebugStringW( wcFile );
					lsn::DebugA( "\r\n" );
				}
			}
		}
	}
	return 0;
}

#endif	// #ifdef LSN_SPC700_CPU_VERIFY

#endif	// #ifdef _WIN32

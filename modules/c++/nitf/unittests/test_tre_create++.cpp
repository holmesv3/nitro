#include <sys/OS.h>

#include <import/nitf.hpp>
#include <nitf/UnitTests.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("test_tre_create_329")
{
    // https://github.com/mdaus/nitro/issues/329

    CHECK(nitf_PluginRegistry_PreloadedTREHandlerEnable("HISTOA", NRT_TRUE));
    nitf::TRE tre("HISTOA", "HISTOA"); // allocates fields SYSTEM .. NEVENTS
    tre.setField("SYSTYPE", "M1");
    CHECK(true);

    //tre.setField("PDATE[0]", "20200210184728"); // aborts program; worked prior to 2.10
    CHECK(true);
}

TEST_CASE("test_tre_clone_329")
{
    // https://github.com/mdaus/nitro/issues/329
    const std::string rd = "begin1020030004ABCDEFend";

    nitf_TRE* rawTre = nullptr;
    {
        nitf_Error error;
        rawTre = nitf::TRE::create("TESTxyz", NITF_TRE_RAW, error);
        CHECK(rawTre != nullptr);

        nitf::TRE::setField(rawTre, "raw_data", rd, error);
        CHECK(true);
    }

    const nitf::TRE tre(rawTre);
    CHECK(true);
    const auto cloneTre = tre.clone();  // leads to free(): invalid size(): in libc.so.6 when the program exits; worked prior to 2.10
    CHECK(true);
}

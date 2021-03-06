#include "stdafx.h"
#include "CppUnitTest.h"
#include "RUNC.h"
#include "CoverCollector.h"
#include "MostCoverCollector.h"
#include "IntegersFileWriter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DualizationLibTest
{
	TEST_CLASS(CoverCollectorsTests)
	{
	public:
		
        TEST_METHOD(CoverCollectorTest)
        {
            CoverCollector c;

            Runc::GlobalState A(Runc::RUNCM);
            A.LoadMatrix("../ao.test/datasets/10_50_7187.hg");
            A.CoverCallback = &c;

            A.Dualize();

            Assert::AreEqual((int)c.GetCovers().size(), 7187);
        }

        TEST_METHOD(MostCoverCollectorTest)
        {
            MostCoverCollector c;
            c.Options.MostCount = 100;
            c.Options.TrimSize = 500;

            Runc::GlobalState A(Runc::RUNCM);
            A.LoadMatrix("../ao.test/datasets/10_50_7187.hg");
            A.CoverCallback = &c;
            A.Dualize();
            c.Trim();

            Assert::IsTrue(c.GetCovers().size()==100);

            IntegersFileWriter w("../ao.test/datasets/10_50_7187_min100.hg");
            w.WriteIntegerMatrix(c.GetCovers());

        }

        TEST_METHOD(BitCoverCollectorTest)
        {
            BitCoverCollectorCallback c;

            Runc::GlobalState A(Runc::RUNCM);
            A.LoadMatrix("../ao.test/datasets/10_50_7187.hg");
            A.CoverCallback = &c;

            A.Dualize();

            Assert::AreEqual(c.GetCovers().width(), 51);

            Assert::AreEqual(c.GetCovers().height(),7187);
            
            
        }

	};
}
set(SOURCE_FILES MultiByBinaryLearner.cpp
        FeatureValue.cpp
#        BoolBinaryOperation.h
        ECmpVoting.h
        ECVotingLearner.h
        Object.cpp
        ECVoting.cpp
        Predictions.h
        Dataset.h
        ECVoting.h
        SamplesWeighter.cpp
        PSVotingLearner.cpp
#        BoostingLogicalCorrector.cpp
        InformativityCondition.h
        EC.h
        ObjectsClass.h
#        ECmpSetPredicateBuilder.cpp
        Interfaces.h
        BinaryECFeatureSelector.h
        ECmpByRankFeatureSelector.cpp
        FTVotingLearner.cpp
        CmpMatrixBuilder.h
        CmpMatrix.h
        BinaryClassifierVoter.h
        Comparers.cpp
        BoostingLearner.cpp
        CmpFitMatrixBuilder.cpp
        FeatureValue.h
        SamplesWeighter.h
        Object.h
        CMakeLists.txt
        ObjectsClass.cpp
        FitMatrix.cpp
        MultiByBinaryLearner.h
        CoverMatrix.h
        InitECFeatureSelector.h
        Comparers.h
        FitMatrix.h
        InitECFeatureSelector.cpp
        CmpMatrix.cpp
        CmpFitMatrixBuilder.h
        ECmpVoting.cpp
        FTVotingLearner.h
        FTFeatureSelector.cpp
        BinaryClassifierAdaptor.cpp
        LazyFeatureSelector.h
        BinaryClassifierVoter.cpp
        ClassFeatureSelector.cpp
        ECmp.h
        CmpMatrixBuilder.cpp
        BinaryECFeatureSelector.cpp
        BinaryClassifierAdaptor.h
        BinaryClassifierNormalizer.cpp
        AlgorithmEstimator.cpp
        FeatureSelectorBase.h
        FTVoting.cpp
        FTVoting.h
        Predictions.cpp
        LazyFeatureSelector.cpp
        Dataset.cpp
#        BoostingLogicalCorrector.h
#        ECmpVotingLearner.h
        AlgorithmEstimator.h
        FTFeatureSelector.h
        ClassFeatureSelector.h
        BinaryLearnerAdaptor.cpp
        ECVotingLearner.cpp
#        BoolBinaryOperation.cpp
        ECmpByRankFeatureSelector.h
#        ECmpSetPredicateBuilder.h
#        ECmpVotingLearner.cpp
        BinaryClassifierBoolAdaptor.h
        FeatureSelectorBase.cpp
        CoverMatrix.cpp
        PSVotingLearner.h
        ECmpSetPredicate.h
        BoostingLearner.h
        BinaryLearnerAdaptor.h
        BinaryClassifierNormalizer.h)


add_library(logical ${SOURCE_FILES})

add_executable(logcls main.cpp)
target_link_libraries(logcls logical dual common ${Boost_LIBRARIES} ${Boost_LIBRARIES} pthread)
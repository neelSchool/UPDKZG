TEST(SRSUpdate, Verify) {
    SRS srs = KGen(8, test_rng);
    Fr beta = Fr::random(test_rng);
    UpdateProof p;
    SRS srs2 = UpdateSRS(srs, beta, p);
    EXPECT_TRUE(VerifyUpdate(srs, srs2, p));
}

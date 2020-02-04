package net.infoxication.reactstarprnt;

import com.facebook.react.bridge.Promise;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;

class RNStarPrntModuleTest {

    @DisplayName("getDefaultPaperWidth should return the correct default paper width for each model")
    @ParameterizedTest(name = "\"{0}\" should be {1}")
    @CsvSource({
        "STAR mPOP-, 384",
        "mPOP, 384",
        "FVP10 (STR_T-001), 576",
        "Star FVP10, 576",
        "TSP113, 576",
        "TSP143, 576",
        "TSP100-, 576",
        "Star TSP113, 576",
        "Star TSP143, 576",
        "TSP654II (STR_T-001), 576",
        "TSP654 (STR_T-001), 576",
        "TSP651 (STR_T-001), 576",
        "TSP743II (STR_T-001), 576",
        "TSP743 (STR_T-001), 576",
        "TSP847II (STR_T-001), 832",
        "TSP847 (STR_T-001), 832",
        "SP712 (STR-001), 210",
        "SP717 (STR-001), 210",
        "SP742 (STR-001), 210",
        "SP747 (STR-001), 210",
        "STAR L200-, 384",
        "STAR L204-, 384",
        "BSC10, 512",
        "Star BSC10, 512",
        "STAR L300-, 576",
        "STAR L304-, 576",
        "MCP20 (STR-001), 384",
        "MCP21 (STR-001), 384",
        "mC-Print2-, 384",
        "mC-Print2, 384",
        "MCP31 (STR-001), 576",
        "mC-Print3-, 576",
        "mC-Print3, 576",
        "TUP592 (STR_T-001), 576",
        "TUP542 (STR_T-001), 576",
        "SK1-211_221, 432",
        "SK1-211_221 Presenter, 432",
        "SK1-311_321, 576",
        "SK1-311 Presenter, 576",
        "STAR mPOP-, 384",
        "mPOP, 384",
        "FVP10 (STR_T-001), 576",
        "Star FVP10, 576",
        "TSP113, 576",
        "TSP143, 576",
        "TSP100-, 576",
        "Star TSP113, 576",
        "Star TSP143, 576",
        "TSP654II (STR_T-001), 576",
        "TSP654 (STR_T-001), 576",
        "TSP651 (STR_T-001), 576",
        "TSP743II (STR_T-001), 576",
        "TSP743 (STR_T-001), 576",
        "TSP847II (STR_T-001), 832",
        "TSP847 (STR_T-001), 832",
        "SP712 (STR-001), 210",
        "SP717 (STR-001), 210",
        "SP742 (STR-001), 210",
        "SP747 (STR-001), 210",
        "STAR L200-, 384",
        "STAR L204-, 384",
        "BSC10, 512",
        "Star BSC10, 512",
        "STAR L300-, 576",
        "STAR L304-, 576",
        "MCP20 (STR-001), 384",
        "MCP21 (STR-001), 384",
        "mC-Print2-, 384",
        "mC-Print2, 384",
        "MCP31 (STR-001), 576",
        "mC-Print3-, 576",
        "mC-Print3, 576",
        "TUP592 (STR_T-001), 576",
        "TUP542 (STR_T-001), 576",
        "SK1-211_221, 432",
        "SK1-211_221 Presenter, 432",
        "SK1-311_321, 576",
        "SK1-311 Presenter, 576",
    })
    void theGetDefaultPaperWidthMethodShouldReturnTheCorrectDefaultPaperWidth(String model, int width) {
        // Given
        Promise mockedPromise = mock(Promise.class);
        RNStarPrntModule rnStarPrntModule = new RNStarPrntModule(null);

        // When
        rnStarPrntModule.getDefaultPaperWidth(model, mockedPromise);

        // Then
        verify(mockedPromise).resolve(width);
    }

    @Test
    void theGetDefaultPaperWidthMethodShouldRejectThePromiseIfTheModelIsNotFound() {
        // Given
        Promise mockedPromise = mock(Promise.class);
        RNStarPrntModule rnStarPrntModule = new RNStarPrntModule(null);

        // When
        rnStarPrntModule.getDefaultPaperWidth("UNKNOWN", mockedPromise);

        // Then
        verify(mockedPromise).reject("Failed", "Failed");
    }
}
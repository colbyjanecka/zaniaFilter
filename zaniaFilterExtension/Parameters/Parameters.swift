//
//  Parameters.swift
//  zaniaFilterExtension
//
//  Created by Colby Janecka on 6/22/25.
//

import Foundation
import AudioToolbox

let zaniaFilterExtensionParameterSpecs = ParameterTreeSpec {
    ParameterGroupSpec(identifier: "global", name: "Global") {
        ParameterSpec(
            address: .gain,
            identifier: "gain",
            name: "Output Gain",
            units: .linearGain,
            valueRange: 0...100,
            defaultValue: 25
        );
        ParameterSpec(
            address: .attack,
            identifier: "attack",
            name: "Attack",
            units: .milliseconds,
            valueRange: 0.0...1000.0,
            defaultValue: 100.0
        );
        ParameterSpec(
            address: .pan,
            identifier: "pan",
            name: "Pan",
            units: .linearGain,
            valueRange: -50...50,
            defaultValue: 0
        );
        ParameterSpec(
            address: .temp,
            identifier: "temp",
            name: "Temp",
            units: .linearGain,
            valueRange: 0.0...5.0,
            defaultValue: 0
        )
    }
}

extension ParameterSpec {
    init(
        address: zaniaFilterExtensionParameterAddress,
        identifier: String,
        name: String,
        units: AudioUnitParameterUnit,
        valueRange: ClosedRange<AUValue>,
        defaultValue: AUValue,
        unitName: String? = nil,
        flags: AudioUnitParameterOptions = [AudioUnitParameterOptions.flag_IsWritable, AudioUnitParameterOptions.flag_IsReadable],
        valueStrings: [String]? = nil,
        dependentParameters: [NSNumber]? = nil
    ) {
        self.init(address: address.rawValue,
                  identifier: identifier,
                  name: name,
                  units: units,
                  valueRange: valueRange,
                  defaultValue: defaultValue,
                  unitName: unitName,
                  flags: flags,
                  valueStrings: valueStrings,
                  dependentParameters: dependentParameters)
    }
}

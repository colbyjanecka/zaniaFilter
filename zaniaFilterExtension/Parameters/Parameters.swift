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
            address: .cutoff,
            identifier: "cutoff",
            name: "Cutoff",
            units: .hertz,
            valueRange: 12.0...20_000.0,
            defaultValue: 20_000,
            unitName: nil,
            flags: [.flag_IsReadable,
                    .flag_IsWritable,
                    .flag_CanRamp],
            valueStrings: nil,
            dependentParameters: nil
        );
        ParameterSpec(
            address: .resonance,
            identifier: "resonance",
            name: "Res",
            units: .decibels,
            valueRange: -20.0...20.0,
            defaultValue: 0.0,
            unitName: nil,
            flags: [.flag_IsReadable,
                    .flag_IsWritable,
                    .flag_CanRamp],
            valueStrings: nil,
            dependentParameters: nil
        );
        ParameterSpec(
            address: .temp,
            identifier: "temp",
            name: "Cutoff",
            units: .ratio,
            valueRange: 0.0...1.0,
            defaultValue: 0.5
        );
        ParameterSpec(
            address: .delayTime,
            identifier: "delayTime",
            name: "Delay",
            units: .milliseconds,
            valueRange: 1...100000,
            defaultValue: 100.0
        );
        ParameterSpec(
            address: .decayFactor,
            identifier: "decayFactor",
            name: "Decay",
            units: .ratio,
            valueRange: 0.0...1.0,
            defaultValue: 0.1
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

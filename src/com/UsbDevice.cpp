/*
 * PLUG - software to operate Fender Mustang amplifier
 *        Linux replacement for Fender FUSE software
 *
 * Copyright (C) 2017-2021  offa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "com/UsbDevice.h"
#include "com/UsbException.h"
#include <array>
#include <libusb-1.0/libusb.h>

namespace plug::com::usb
{
    Device::Device(libusb_device* device, std::uint16_t vid, std::uint16_t pid, std::uint8_t stringDescriptorIndex)
        : device_(libusb_ref_device(device)), handle_(nullptr), vid_(vid), pid_(pid), stringDescriptorIndex_(stringDescriptorIndex)
    {
    }

    Device::Device(libusb_device* device)
        : device_(libusb_ref_device(device)), handle_(nullptr)
    {
        libusb_device_descriptor descriptor;

        if (const auto result = libusb_get_device_descriptor(device, &descriptor); result != LIBUSB_SUCCESS)
        {
            libusb_unref_device(device_);
            throw UsbException{result};
        }
        vid_ = descriptor.idVendor;
        pid_ = descriptor.idProduct;
        stringDescriptorIndex_ = descriptor.iProduct;
    }

    Device::~Device()
    {
        close();
        libusb_unref_device(device_);
    }

    void Device::open()
    {
        if (const int result = libusb_open(device_, &handle_); result != LIBUSB_SUCCESS)
        {
            throw UsbException{result};
        }
    }

    void Device::close()
    {
        if (handle_ != nullptr)
        {
            libusb_close(handle_);
            handle_ = nullptr;
        }
    }

    bool Device::isOpen() const noexcept
    {
        return handle_ != nullptr;
    }

    std::uint16_t Device::vendorId() const noexcept
    {
        return vid_;
    }

    std::uint16_t Device::productId() const noexcept
    {
        return pid_;
    }

    std::string Device::name()
    {
        std::array<unsigned char, 256> buffer;
        const int n = libusb_get_string_descriptor_ascii(handle_, stringDescriptorIndex_, buffer.data(), buffer.size());

        if (n < 0)
        {
            throw UsbException{n};
        }
        return std::string{buffer.cbegin(), std::next(buffer.cbegin(), n)};
    }
}

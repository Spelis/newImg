use clap::Parser;
use image::RgbImage;
use regex::Regex;

#[derive(Parser, Debug)]
struct Args {
	input: String,
}

#[derive(Debug, Clone, Copy)]
struct IVec2 {
	x: u32,
	y: u32,
}

#[derive(Debug)]
struct Nimg {
	name: String,
	ext: String,
	size: IVec2,
}

impl Nimg {
	fn into(input: String) -> Nimg {
		let parts: Vec<String> = input.split(".").map(str::to_string).collect();
		let size: (u32, u32) = {
			let nums: Vec<u32> = parts[2]
				.split('x')
				.map(|s| s.parse::<u32>().unwrap())
				.collect();

			let [w, h]: [u32; 2] = nums.try_into().unwrap();
			(w, h)
		};

		Nimg {
			name: parts[0].clone(),
			ext: parts[1].clone(),
			size: IVec2 {
				x: size.0,
				y: size.1,
			},
		}
	}
}

fn main() {
	let filename = Args::parse().input;
	let re = Regex::new(r"^.+\.\w+\.\d+x\d+\.nimg$").unwrap();
	if re.is_match(filename.as_str()) {
		let data: Nimg = Nimg::into(filename);
		dbg!(&data);
		let img = RgbImage::new(data.size.x, data.size.y);
		img.save(format!("{}.{}", data.name, data.ext)).unwrap();
	} else {
		panic!(
			"Invalid filename \"{}\". Must be in the \"fn.ext.WxH.nimg\" format.",
			filename
		);
	}
}

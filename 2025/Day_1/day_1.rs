//The puzzle is a lock that has 0-99 and is a circle
//We want to have a counter that can increase/decrease by a set amount
//R10 would Increase the number by 10
//L5 would decrease the number by 5
//EX) Starting from 0 
//R10 L5 L10 R2 R8
//0 -> 10 -> 5 -> 95 -> 97 -> 5
//
use std::io::{self, Read};

const MOD: i32 = 100;

fn part1(input: &str) -> u32 {
    input.lines().fold((50, 0), |(pos, count), line| {
        let (dir, dist) = line.split_at(1);
        let dist: i32 = dist.parse().unwrap();
        let new_pos = match dir {
            "L" => (pos - dist).rem_euclid(MOD),
            "R" => (pos + dist).rem_euclid(MOD),
            _ => panic!("Invalid direction"),
        };
        (new_pos, count + if new_pos == 0 { 1 } else { 0 })
    }).1
}

fn part2(input: &str) -> u32 {
    input.lines().fold((50, 0), |(pos, count), line| {
        let (dir, dist) = line.split_at(1);
        let dist: i32 = dist.parse().unwrap();
        let new_pos = match dir {
            "L" => (pos - dist).rem_euclid(MOD),
            "R" => (pos + dist).rem_euclid(MOD),
            _ => panic!("Invalid direction"),
        };

        // Count how many times we pass through 0
        let mut extra = 0;
        match dir {
            "L" => {
                // going left decreases
                let mut p = pos;
                for _ in 0..dist {
                    p = (p - 1).rem_euclid(MOD);
                    if p == 0 { extra += 1; }
                }
            }
            "R" => {
                let mut p = pos;
                for _ in 0..dist {
                    p = (p + 1).rem_euclid(MOD);
                    if p == 0 { extra += 1; }
                }
            }
            _ => {}
        }

        (new_pos, count + extra)
    }).1
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();

    let start = std::time::Instant::now();
    let ans1 = part1(&input);
    println!("Part 1 result: {}", ans1);
    println!("Part 1 time: {:?}", start.elapsed());

    let start = std::time::Instant::now();
    let ans2 = part2(&input);
    println!("Part 2 result: {}", ans2);
    println!("Part 2 time: {:?}", start.elapsed());
}

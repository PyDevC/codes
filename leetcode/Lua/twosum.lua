local function two_sum(nums, target)
    local cache = {}
    for idx, val in ipairs(nums) do
        local comp = target - val
        if cache[val] then
            return { cache[val], idx }
        end
        cache[comp] = idx
    end
end

local nums = { 2, 7, 11, 15 }
local target = 9
print(table.concat(two_sum(nums, target), ", "))

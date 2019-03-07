﻿using System;

namespace FluidHTN.Conditions
{
	public class FuncCondition<T> : ICondition where T : IContext
	{
		public string Name { get; }
		private readonly Func< T, bool > _func;

		public FuncCondition( string name, Func< T, bool > func )
		{
			Name = name;
			_func = func;
		}

		public bool IsValid( IContext ctx )
		{
			if ( ctx is T c )
			{
				return _func?.Invoke( c ) ?? false;
			}
			else
			{
				throw new Exception("Unexpected context type!");
			}
		}
	}
}